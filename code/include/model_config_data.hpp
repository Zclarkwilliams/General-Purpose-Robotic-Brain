#pragma once

//	Standard libraries
#include <vector>
#include <memory>
#include <sstream>

class NeuralModel {
    public:
        typedef struct {
            std::string name;
			std::string id;
            std::string enabled;
            std::string tonicstimulus;
            std::string noise;
            std::string restingpot;
            std::string size;
            std::string timeconst;
            std::string initthresh;
            std::string relativeaccom;
            std::string accomtimeconst;
            std::string ahpamp;
            std::string ahptimeconst;
            std::string gmaxca;
            std::string burstinitatbottom;
            std::string caactive_id;
            std::string caactive_midpoint;
            std::string caactive_slope;
            std::string caactive_timeconst;
            std::string caactive_activatetype;
            std::string cadeactive_id;
            std::string cadeactive_midpoint;
            std::string cadeactive_slope;
			std::string cadeactive_timeconst;
			std::string cadeactive_activatetype;
		} Neurons;

		typedef struct {
			std::string name;
			std::string id;
			std::string type;
			std::string equil;
			std::string synamp;
			std::string saturatev;
		} SynapsesNonSpiking;

		typedef struct {
			std::string name;
			std::string id;
			std::string type;
			std::string equil;
			std::string synamp;
			std::string decay;
			std::string relfacil;
			std::string facildecay;
			std::string voltdep;
			std::string maxrelcond;
			std::string satpspot;
			std::string threshpspot;
			std::string hebbian;
			std::string maxaugcond;
			std::string learninginc;
			std::string learningtime;
			std::string allowforget;
			std::string forgettime;
			std::string consolidation;
		} SynapsesSpiking;

		typedef struct {
			std::string name;
			std::string id;
			std::string type;
			std::string lowcoup;
			std::string hicoup;
			std::string turnonv;
			std::string saturatev;
		} SynapsesElectrical;

		typedef struct {
			std::string id;
			std::string sourceid;
			std::string targetid;
			std::string type;
			std::string synapsetypeid;
			std::string delay;
			std::string g;
		} Connexions;

		// Structure to contain the organisms data as vector structs
		//typedef struct {
		struct Organisms {
			std::string 	organism_id;
			std::string 	organism_name;
			std::string 	neuralmodule_id;
			std::string 	neuralmodule_name;
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
		};

		// Instantiate and generate the organism vector struct
		std::vector<Organisms>	organismVector;

		// Variable member of class to hold the path to the Animatlab Neural Model Configuration
		std::string configFilePath;

		// Consructor and Destructor functions for class
		NeuralModel() {}
		~NeuralModel() {}
		
		// Access the main function that will parse and get datat from config file
		int parse_config_file();
		void get_config_file_path(void);
		
		void print_val(std::string, const std::string&);

		// Transfering the configuration model data from the Host(CPU) to the Device(GPU) cache
		//void transferOrganism(void);
		//void transferNeurons(struct Organisms*);
		//void transferNonSpikingSynapses(struct Organisms*);
		//void transferConnexions(struct Organisms*);
};
