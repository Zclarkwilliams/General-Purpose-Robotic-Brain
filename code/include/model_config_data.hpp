#pragma once

//	Standard libraries
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>

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
        typedef struct{
            const std::string* 	organism_id;
            const std::string* 	organism_name;
            const std::string* 	neuralmodule_id;
            const std::string* 	neuralmodule_name;
            // Generate the vector structs for each section of the model
            std::vector<std::unique_ptr<Neurons>>               neuronVector;
            std::vector<std::unique_ptr<Connexions>>            connexionVector;
            std::vector<std::unique_ptr<SynapsesSpiking>>       spikingVector;
            std::vector<std::unique_ptr<SynapsesElectrical>>    electricalVector;
            std::vector<std::unique_ptr<SynapsesNonSpiking>>    nonspikingVector;
        } Organisms;

        // Instantiate and generate the organism vector struct
        std::vector<std::shared_ptr<Organisms>>	organismVector;

        // Instantiate the structs for each data set
        Neurons				neuronStruct;
        Connexions			connexionStruct;
        SynapsesSpiking		spikingStruct;
        SynapsesElectrical  electricalStruct;
        SynapsesNonSpiking	nonspikingStruct;
        Organisms*		    organismStruct;

        char configFilePath[];


        // Access the main function that will parse and get datat from config file
        NeuralModel() {}
        ~NeuralModel() {}
        //void init_vectors();
        int parse_model_config();
        //void add_characteristic(const int child, const char* field, const char* val);

};
/*
void init_vector()
{
    NeuralModel::organism = std::make_unique<NeuralModel::Organisms>(organism)
}
*/
/*
void NeuralModel::add_characteristic(const int child, const char* field, const char* val)
{
    switch(child){
        case ORGANISM:
            switch(field){
                case 'name':
                    break;
                case 'id':
                    break;
                case 'enabled':
                    break;
                case 'tonicstimulus':
                    break;
                case 'noise':
                    break;
                case 'restingpot':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
                case 'size':
                    break;
            }
            break;
        case NEURON:
            break;
        case SPIKING:
            break;
        case NONSPIKING:
            break;
        case ELECTRICAL:
            break;
        case CONNEXION:
            break;
    }
};
*/