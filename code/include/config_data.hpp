#pragma once

//	Standard libraries
#include <vector>
#include <memory>
#include <sstream>

//	Non-Standard libraries
#include "pugixml.hpp"

class SimulationModel {
    public:
		typedef struct {
			std::string id;
			std::string modulename;
			std::string modulefilename;
			std::string type;
			std::string timestep;
			std::string spikepeak;
			std::string spikestrength;
			std::string ahpequilpot;
			std::string caequilpot;
			std::string absoluterefr;
			std::string usecriticalperiod;
			std::string startcriticalperiod;
			std::string endcriticalperiod;
			std::string ttx;
			std::string cd;
			std::string hh;
			std::string freezehebb;
			std::string retainhebbmemory;
		} NeuralModel;

		typedef struct {
			std::string id;
			std::string name;
			std::string alwaysactive;
			std::string enabled;
			std::string type;
			std::string currenttype;
			std::string organismid;
			std::string targetnodeid;
			std::string starttime;
			std::string endtime;
			std::string cycleonduration;
			std::string cycleoffduration;
			std::string burstonduration;
			std::string burstoffduration;
			std::string currenton;
			std::string currentoff;
			std::string currentonequation;
		} ExternalStimuli;

		typedef struct {
			std::string name;
			std::string id;
			std::string type;
			std::string equil;
			std::string synamp;
			std::string threshv;
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

		//typedef struct {
		struct Neurons{
			std::vector<double> G_s;
			double V;

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

			//	data configuring the synaptic connexions per neuron
			std::vector<Connexions>	connexionVector;
		};

		// Structure to contain the organisms data as vector structs
		//typedef struct {
		struct Organisms {
			std::string 	organism_id;
			std::string 	organism_name;
			std::string 	neuralmodule_id;
			std::string 	neuralmodule_name;
			
			// This is the struct with the global settings for the organism
			std::vector<NeuralModel> neuralmodelVector;

			// Generate the vector structs for each section of the model
			std::vector<Neurons>               neuronVector;
			std::vector<SynapsesSpiking>       spikingVector;
			std::vector<SynapsesElectrical>    electricalVector;
			std::vector<SynapsesNonSpiking>    nonspikingVector;
		};

		// Instantiate and generate the organism vector struct
		std::vector<Organisms>			organismVector;
		std::vector<ExternalStimuli>	externalstimuliVector;

		// Variable member of class to hold the path to the Animatlab Neural Model Configuration
		std::string configFilePath;

		// Capture the counters for the number of the different members
		static unsigned int numNeurons;
		unsigned int numOrganisms;
		unsigned int numConnexions;
		unsigned int numExternalStimuli;
		unsigned int numSpikingSynapses;
		unsigned int numNonSpikeSynapses;
		unsigned int numElectricalSynapses;

		// Consructor and Destructor functions for class
		SimulationModel() {}
		~SimulationModel() {}
		
		// Access the main function that will parse and get datat from config file
		int parse_config_file();
		void get_config_file_path(void);
		
		void print_val(std::string, const std::string&);

		// Getting the config data functions
		int Get_Organisms(pugi::xml_node);
		int Get_ExternalStimuli(pugi::xml_node);
		int Get_NeruonModel(pugi::xml_node_iterator, struct Organisms*);
		int Get_Neurons(pugi::xml_node_iterator, struct Organisms*);
		int Get_Connexions(pugi::xml_node_iterator, struct Organisms*);
		int Get_Synapse_Spiking(pugi::xml_node, struct Organisms*);
		int Get_Synapse_NonSpiking(pugi::xml_node, struct Organisms*);
		int Get_Synapse_Electrical(pugi::xml_node, struct Organisms*);

		// Transfering the configuration model data from the Host(CPU) to the Device(GPU) cache
		void transferOrganism(void);
		void transferNeurons(struct Organisms*);
		void transferNonSpikingSynapses(struct Organisms*);
		void transferConnexions(struct Neurons *);
};
