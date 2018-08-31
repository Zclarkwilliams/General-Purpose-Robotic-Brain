#pragma once

//	Standard libraries
#include <vector>
#include <memory>
#include <sstream>

class NeuralModel {
    public:
        typedef struct {
            const std::string* name;
            const std::string* id;
            const std::string* enabled;
            const std::string* tonicstimulus;
            const std::string* noise;
            const std::string* restingpot;
            const std::string* size;
            const std::string* timeconst;
            const std::string* initthresh;
            const std::string* relativeaccom;
            const std::string* accomtimeconst;
            const std::string* ahpamp;
            const std::string* ahptimeconst;
            const std::string* gmaxca;
            const std::string* burstinitatbottom;
            const std::string* caactive_id;
            const std::string* caactive_midpoint;
            const std::string* caactive_slope;
            const std::string* caactive_timeconst;
            const std::string* caactive_activatetype;
            const std::string* cadeactive_id;
            const std::string* cadeactive_midpoint;
            const std::string* cadeactive_slope;
			const std::string* cadeactive_timeconst;
			const std::string* cadeactive_activatetype;
		} Neurons;

		typedef struct {
			const std::string* name;
			const std::string* id;
			const std::string* type;
			const std::string* equil;
			const std::string* synamp;
			const std::string* saturatev;
		} SynapsesNonSpiking;

		typedef struct {
			const std::string* name;
			const std::string* id;
			const std::string* type;
			const std::string* equil;
			const std::string* synamp;
			const std::string* decay;
			const std::string* relfacil;
			const std::string* facildecay;
			const std::string* voltdep;
			const std::string* maxrelcond;
			const std::string* satpspot;
			const std::string* threshpspot;
			const std::string* hebbian;
			const std::string* maxaugcond;
			const std::string* learninginc;
			const std::string* learningtime;
			const std::string* allowforget;
			const std::string* forgettime;
			const std::string* consolidation;
		} SynapsesSpiking;

		typedef struct {
			const std::string* name;
			const std::string* id;
			const std::string* type;
			const std::string* lowcoup;
			const std::string* hicoup;
			const std::string* turnonv;
			const std::string* saturatev;
		} SynapsesElectrical;

		typedef struct {
			const std::string* id;
			const std::string* sourceid;
			const std::string* targetid;
			const std::string* type;
			const std::string* synapsetypeid;
			const std::string* delay;
			const std::string* g;
		} Connexions;

		// Structure to contain the organisms data as vector structs
		typedef struct {
			const std::string* 	organism_id;
			const std::string* 	organism_name;
			const std::string* 	neuralmodule_id;
			const std::string* 	neuralmodule_name;
			// Generate the vector structs for each section of the model
		/*	std::vector<std::shared_ptr<Neurons>>               neuronVector;
			std::vector<std::shared_ptr<Connexions>>            connexionVector;
			std::vector<std::shared_ptr<SynapsesSpiking>>       spikingVector;
			std::vector<std::shared_ptr<SynapsesElectrical>>    electricalVector;
			std::vector<std::shared_ptr<SynapsesNonSpiking>>    nonspikingVector;
		*/
			std::vector<Neurons>               neuronVector;
			std::vector<Connexions>            connexionVector;
			std::vector<SynapsesSpiking>       spikingVector;
			std::vector<SynapsesElectrical>    electricalVector;
			std::vector<SynapsesNonSpiking>    nonspikingVector;
		} Organisms;

		// Variable member of class to hold the path to the Animatlab Neural Model Configuration
		std::string configFilePath;

		// Consructor and Destructor functions for class
		NeuralModel() {}
		~NeuralModel() {}
		
		// Access the main function that will parse and get datat from config file
		int parse_config_file();
		void get_config_file_path(void);
		void print_val(std::string, const std::string&);
		//void printVect(std::vector<std::string>const& vect);
};