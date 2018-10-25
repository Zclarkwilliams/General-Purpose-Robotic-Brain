#ifndef SYSTEM_DEFINES
#define SYSTEM_DEFINES

//	Error Handler Constants
const int SYSTEM_LOC_MASK = 0xFF00;
const int ERROR_BYTE = 4;

//	Config Parser Errors
const int ERR_CFG_PRSR = 0x0100;
/*
const int ERROR_FILE_LOAD = 1;
const int WARNING_ORGANISM_SIZE_MISMATCH = 2;
const int WARNING_NEURONAL_SIZE_MISMATCH = 3;
const int WARNING_CONNEXION_SIZE_MISMATCH = 4;
const int WARNING_SYNAPSE_SPIKING_SIZE_MISMATCH = 5;
const int WARNING_SYNAPSE_NONSPIKING_SIZE_MISMATCH = 6;
const int WARNING_SYNAPSE_ELECTRICAL_SIZE_MISMATCH = 7;
*/

//	Encode Parsed NN Errors
const int ERR_ENCODING_NN = 0x0200;


//	Main System Errors (other errors)
const int ERR_MAIN_SYS = 0x0000;




//  child types for assigning values to vecotr structs
const int ORGANISM      = 0;
const int NEURON        = 1;
const int SPIKING       = 2;
const int NONSPIKING    = 3;
const int ELECTRICAL    = 4;
const int CONNEXION     = 5;

#endif // SYSTEM_DEFINES

