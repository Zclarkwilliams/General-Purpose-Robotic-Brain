#include <PID_v1.h>   // use PID library
#define PWM_PIN 5

//From MATLAB:
//'0' means STOP
//'1' means MANUAL SPEED INPUT
//'2' means SPEED PROFILE

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
double prevMillis = 0;
//double timeChange = 0;
int sampleTime = 5;
// variables to hold values for the encoder. The inputs are 2 and 13 (and optionally A6 for the index).
const int ENCODER_EDGES_PER_ROTATION = 2048 * 4;
const int ENCODER_SAMPLES_PER_SECOND = 2;
const int LOOP_DELAY_MS = 0;

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
int optionFromPC = 0;
float sFromPC = 0;
float t1FromPC = 0;
float t2FromPC = 0;
float t3FromPC = 0;

// variables to be used for the closed loop
float desiredSpeed = 0;
//float Error = 0;
//float errSum = 0;
double desiredHz = 0;
double actualHz = 0;
float actualMPH = 0;
double PWMOutput = 0;
int INPUT_TIMING_PIN = 11;
int InputTime = 0;
double  Kp = .5, Ki = .25, Kd = 0;

PID motorPID(&actualHz, &PWMOutput, &desiredHz, Kp, Ki, Kd, DIRECT); // specify parameters for controller

boolean newData = false;

//variables to define the transformations (based on measurements)
float dShaft = 1; // inches
float dWheel = 2.4; //inches
float dRoller = 1.92; //inches

///||\\\||///||\\\||///||\\\||///||\\\

void setup() {
  Serial.begin(115200);
  pinMode(INPUT_TIMING_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  // Setup Quadrature Encoder
  REG_PMC_PCER0 = PMC_PCER0_PID27
                  | PMC_PCER0_PID28
                  | PMC_PCER0_PID29;

  // Setup a channel in waveform mode
  REG_TC0_CMR2 = TC_CMR_TCCLKS_TIMER_CLOCK4
                 | TC_CMR_WAVE
                 | TC_CMR_ACPC_TOGGLE
                 | TC_CMR_WAVSEL_UP_RC;

  //Define the sample period
  REG_TC0_RC2 = F_CPU / 128 / ENCODER_SAMPLES_PER_SECOND;

  // Setup a channel in capture mode
  REG_TC0_CMR0 = TC_CMR_ABETRG
                 | TC_CMR_LDRA_EDGE
                 | TC_CMR_LDRB_EDGE
                 | TC_CMR_ETRGEDG_EDGE
                 | TC_CMR_CPCTRG;

  // Enable features, noting Speed not Position is chosen
  REG_TC0_BMR = TC_BMR_QDEN
                | TC_BMR_SPEEDEN
                | TC_BMR_EDGPHA;

  // Set everything going
  REG_TC0_CCR0 = TC_CCR_CLKEN | TC_CCR_SWTRG;
  REG_TC0_CCR1 = TC_CCR_CLKEN | TC_CCR_SWTRG;
  REG_TC0_CCR2 = TC_CCR_CLKEN | TC_CCR_SWTRG;

  startMillis = millis();
  motorPID.SetSampleTime(sampleTime);
  motorPID.SetOutputLimits(0, 255);
  motorPID.SetMode(AUTOMATIC);
}

///||\\\||///||\\\||///||\\\||///||\\\

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    defineOption();
    newData = false;
  }
}

///||\\\||///||\\\||///||\\\||///||\\\

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

///||\\\||///||\\\||///||\\\||///||\\\

void parseData() {      // split the data into its parts
  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
  optionFromPC = atof(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  sFromPC = atof(strtokIndx);     // speed input is in MPH

  strtokIndx = strtok(NULL, ",");
  t1FromPC = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  t2FromPC = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  t3FromPC = atof(strtokIndx);
}

///||\\\||///||\\\||///||\\\||///||\\\

void defineOption() {
  switch (optionFromPC) {
    case 0 :
      stopRunning();
      break;
    case 1 :
      manualControl();
      break;
    case 2 :
      speedProfile();
      break;
  }
}

///||\\\||///||\\\||///||\\\||///||\\\

void stopRunning() {
  analogWrite(PWM_PIN, 0);
}

///||\\\||///||\\\||///||\\\||///||\\\

void manualControl() {

  currentMillis = millis() - startMillis;
  int prevMillis = -1;
  while (Serial.available() == 0) {

    InputTime = InputTime ^ 0x01; //Toggle pin when input signal starts over.
    digitalWrite(INPUT_TIMING_PIN, InputTime);

    //Rotations per second, from encoder
    int iSpeedPPP = REG_TC0_RA0;    // Pulses Per sample Period
    actualHz = ((iSpeedPPP / (ENCODER_EDGES_PER_ROTATION * 1.0)) * ENCODER_SAMPLES_PER_SECOND);

    desiredHz = convertToHz(sFromPC);

    motorPID.Compute(); //call out the PID() function

    // Write the PID output to the pin
    if (PWMOutput > 255) {
      analogWrite(PWM_PIN, 255);
    }
    else if (PWMOutput < 0) {
      analogWrite(PWM_PIN, 0);
    }

    else {
      analogWrite(PWM_PIN, PWMOutput);
    }

    actualMPH = convertToMPH(actualHz);

    //Write the output to serial every .5 seconds
    float timeInSec = currentMillis;
    timeInSec /= 1000;
    if (currentMillis % 500 == 0 && prevMillis != currentMillis) {
      Serial.println(timeInSec);
      Serial.println(actualMPH);
    }
    prevMillis = currentMillis;
    currentMillis = millis() - startMillis;
  }
}

///||\\\||///||\\\||///||\\\||///||\\\

void speedProfile() {
  double slope1 = sFromPC / t1FromPC;
  double slope2 = -sFromPC / (t3FromPC - t2FromPC);

  int    t1 = t1FromPC * 1000; //convert times to ms
  int    t2 = t2FromPC * 1000;
  int    t3 = t3FromPC * 1000;

  startMillis = millis();
  currentMillis = millis() - startMillis;

  while (currentMillis <= t3) {
    //Rotations per second, from encoder
    int iSpeedPPP = REG_TC0_RA0;    // Pulses Per sample Period
    actualHz = ((iSpeedPPP / (ENCODER_EDGES_PER_ROTATION * 1.0)) * ENCODER_SAMPLES_PER_SECOND);

    if (currentMillis <= t1) {
      desiredSpeed = currentMillis * slope1 / 1000;
    }
    else if (currentMillis >> t1 && currentMillis <= t2) {
      desiredSpeed = sFromPC;
    }
    else if (currentMillis >= t2) {
      desiredSpeed = (sFromPC + (currentMillis - t2) * slope2 / 1000);
    }

    desiredHz = convertToHz(desiredSpeed);
    motorPID.Compute(); //call out the PID() function

    // Write the PID output to the pin
    if (PWMOutput > 255) {
      analogWrite(PWM_PIN, 255);
    }
    else if (PWMOutput < 0) {
      analogWrite(PWM_PIN, 0);
    }
    else {
      analogWrite(PWM_PIN, PWMOutput);
    }

    actualMPH = convertToMPH(actualHz);

    //Write the output to serial every .5 seconds
    float timeInSec = currentMillis;
    timeInSec /= 1000;
    int everyHalfSec = currentMillis % 500;
    if (everyHalfSec == 0 && prevMillis != currentMillis) {
      Serial.println(timeInSec);
      Serial.println(actualMPH);
    }
    prevMillis = currentMillis;
    currentMillis = millis() - startMillis;
  }
}

///||\\\||///||\\\||///||\\\||///||\\\

float convertToMPH(float Hz) {
  float MPH = PI / 17.6 * (Hz * dShaft * dRoller / dWheel); //MPH
  return  MPH;
}

///||\\\||///||\\\||///||\\\||///||\\\

float convertToHz (float MPH) {
  float vInHz = 17.6 / PI  * (MPH * dWheel / (dShaft * dRoller)); //Hz
  return vInHz;
}


