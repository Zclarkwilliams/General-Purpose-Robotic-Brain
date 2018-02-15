using namespace std;

//	Standard libraries
#include <vector>
#include <sstream>
#include <iostream>
//	Non-Standard libraries
#include "pugixml.hpp"

const int ERROR_FILE_LOAD = -1;

typedef struct{
	const string* name;
	const string* id;
	const string* enabled;
	const string* tonicstimulus;
	const string* noise;
	const string* restingpot;
	const string* size;
	const string* timeconst;
	const string* initthresh;
	const string* relativeaccom;
	const string* accomtimeconst;
	const string* ahpamp;
	const string* ahptimeconst;
	const string* gmaxca;
	const string* burstinitatbottom;
	const string* caactive_id;
	const string* caactive_midpoint;
	const string* caactive_slope;
	const string* caactive_timeconst;
	const string* caactive_activatetype;
	const string* cadeactive_id;
	const string* cadeactive_midpoint;
	const string* cadeactive_slope;
	const string* cadeactive_timeconst;
	const string* cadeactive_activatetype;
} Neurons;

typedef struct {
	const string* name;
	const string* id;
	const string* type;
	const string* equil;
	const string* synamp;
	const string* saturatev;
} Synapses;

typedef struct {
	const string* id;
	const string* sourceid;
	const string* targetid;
	const string* type;
	const string* synapsetypeid;
	const string* delay;
	const string* g;
}Connexions;

typedef struct{

	const string* organism_name;
	const string* organism_id;
	const string* neuralmodule_name;
	const string* neuralmodule_id;

	/*
	typedef std::vector<Neurons> neuron;
	typedef std::vector<Synapses> synapse;
	typedef std::vector<Connexions> connexion;
	*/
	Neurons neuron[100];
	Synapses synapse[100];
	Connexions connexion[100];

}Organisms;

int main(){
	//Organisms orgs;
	//std::vector<Organisms> organism;
	//std::vector<vector<Organisms>> neuron;
	//std::vector<vector<Organisms>> synapse;
	//std::vector<vector<Organisms>> connexion;

	Organisms organism[100];

	const char* filepath = "test_file.asim";
	//const char*	nodepath = "//Simulation/Environment/Organisms/NervousSystem/NeuralModules";
	
	char exit = 0;

	pugi::xml_document doc;

	pugi::xml_node_iterator neuron_child;
	pugi::xml_node_iterator organism_child;
	pugi::xml_node_iterator connexion_child;
	//	Synapse Nodes (3 types; Spiking, Non-Spiking, Electrical)
	pugi::xml_node_iterator synapseelec_child;
	pugi::xml_node_iterator synapsespike_child;
	pugi::xml_node_iterator synapsenospike_child;
	
	pugi::xml_parse_result result = doc.load_file(filepath);
	if (!result){
		return  ERROR_FILE_LOAD;
	}
	cout << "File " << filepath << " Loaded Sucessfully " << endl << endl;
	
	//	Set parent node to start traversing file from
	pugi::xml_node organism_parent = doc.child("Simulation").child("Environment").child("Organisms");
	//	Create array object for the iteration and struct array
	pugi::xml_object_range<pugi::xml_node_iterator> organismlist = organism_parent.children();

	unsigned int numOrganisms = 0;
	for (organism_child = organismlist.begin(); organism_child != organismlist.end(); organism_child++)
	{
		//	Push back new organism created with default constructor
		//organism.push_back(Organisms());

		//	Get the Name of the Organism
		organism[numOrganisms].organism_name = (const string*)organism_parent.child("Organsim").child("Name").text().as_string();
		organism[numOrganisms].organism_id = (const string*)organism_parent.child("Organsim").child("ID").text().get();
		//cout << "Organism Name: " << organism[numOrganisms].organism_name << "\nOrganism ID: " << organism[numOrganisms].organism_id << endl;

		/*************************************************************************************************************************************\
		|
		|		Neuron Section - 
		|
		\*************************************************************************************************************************************/
		//neuron.push_back(orgs());
		pugi::xml_node neuralModule = (*organism_child).child("NervousSystem").child("NeuralModules").child("NeuralModule");
		pugi::xml_object_range<pugi::xml_node_iterator> neuronlist = neuralModule.child("Neurons").children();
		
		unsigned int numNeurons = 0;
		for (neuron_child = neuronlist.begin(); neuron_child != neuronlist.end(); neuron_child++){
			/*
			cout << "Name: "					<< (*neuron_child).child("Name").child_value()				<< endl;
			cout << "\tID: "					<< (*neuron_child).child("ID").child_value() 				<< endl;
			cout << "\tEnabled: "				<< (*neuron_child).child("Enabled").child_value() 			<< endl;
			cout << "\tTonic Stimulus: "		<< (*neuron_child).child("TonicStimulus").child_value() 	<< endl;
			cout << "\tNoise: "					<< (*neuron_child).child("Noise").child_value() 			<< endl;
			cout << "\tResting potential: "		<< (*neuron_child).child("RestingPot").child_value()		<< endl;
			cout << "\tSize: "					<< (*neuron_child).child("Size").child_value() 				<< endl;
			cout << "\tTime Const: "			<< (*neuron_child).child("TimeConst").child_value() 		<< endl;
			cout << "\tInitial threshold: "		<< (*neuron_child).child("InitialThresh").child_value()		<< endl;		
			cout << "\tRelative Accom: "		<< (*neuron_child).child("RelativeAccom").child_value() 	<< endl;
			cout << "\tAccom Time Const: "		<< (*neuron_child).child("AccomTimeConst").child_value()	<< endl;
			cout << "\tAHP Amp: "				<< (*neuron_child).child("AHPAmp").child_value() 			<< endl;
			cout << "\tAHP Time Const: "		<< (*neuron_child).child("AHPTimeConst").child_value() 		<< endl;
			cout << "\tGMaxCa: "				<< (*neuron_child).child("GMaxCa").child_value() 			<< endl;
			cout << "\tBurst Init At Bottom: "	<< (*neuron_child).child("BurstInitAtBottom").child_value()	<< endl;
			cout << "\t" << (*neuron_child).child("CaActivation").name() << endl;
			cout << "\t\tID: "					<< (*neuron_child).child("CaActivation").child("ID").child_value()				<< endl;
			cout << "\t\tMidpoint: "			<< (*neuron_child).child("CaActivation").child("MidPoint").child_value()		<< endl;
			cout << "\t\tSlope: "				<< (*neuron_child).child("CaActivation").child("Slope").child_value()			<< endl;
			cout << "\t\tTime Constant: "		<< (*neuron_child).child("CaActivation").child("TimeConstant").child_value()	<< endl;
			cout << "\t\tActivation Type: "		<< (*neuron_child).child("CaActivation").child("ActivationType").child_value()	<< endl;
			cout << "\t" << (*neuron_child).child("CaDeactivation").name() << endl;
			cout << "\t\tID: "					<< (*neuron_child).child("CaDeactivation").child("ID").child_value()				<< endl;
			cout << "\t\tMidpoint: "			<< (*neuron_child).child("CaDeactivation").child("MidPoint").child_value()			<< endl;
			cout << "\t\tSlope: "				<< (*neuron_child).child("CaDeactivation").child("Slope").child_value()				<< endl;
			cout << "\t\tTime Constant: "		<< (*neuron_child).child("CaDeactivation").child("TimeConstant").child_value()		<< endl;
			cout << "\t\tActivation Type: "		<< (*neuron_child).child("CaDeactivation").child("ActivationType").child_value()	<< endl;
			cout << "}" << endl;
			*/
			organism[numOrganisms].neuron[numNeurons].name						= (const string*)(*neuron_child).child("Name").text().get();
			organism[numOrganisms].neuron[numNeurons].id						= (const string*)(*neuron_child).child("ID").text().get();
			organism[numOrganisms].neuron[numNeurons].enabled					= (const string*)(*neuron_child).child("Enabled").text().get();
			organism[numOrganisms].neuron[numNeurons].tonicstimulus				= (const string*)(*neuron_child).child("TonicStimulus").text().get();
			organism[numOrganisms].neuron[numNeurons].noise						= (const string*)(*neuron_child).child("Noise").text().get();
			organism[numOrganisms].neuron[numNeurons].restingpot				= (const string*)(*neuron_child).child("RestingPot").text().get();
			organism[numOrganisms].neuron[numNeurons].size						= (const string*)(*neuron_child).child("Size").text().get();
			organism[numOrganisms].neuron[numNeurons].timeconst					= (const string*)(*neuron_child).child("TimeConst").text().get();
			organism[numOrganisms].neuron[numNeurons].initthresh				= (const string*)(*neuron_child).child("InitialThresh").text().get();
			organism[numOrganisms].neuron[numNeurons].relativeaccom				= (const string*)(*neuron_child).child("RelativeAccom").text().get();
			organism[numOrganisms].neuron[numNeurons].accomtimeconst			= (const string*)(*neuron_child).child("AccomTimeConst").text().get();
			organism[numOrganisms].neuron[numNeurons].ahpamp					= (const string*)(*neuron_child).child("AHPAmp").text().get();
			organism[numOrganisms].neuron[numNeurons].ahptimeconst				= (const string*)(*neuron_child).child("AHPTimeConst").text().get();
			organism[numOrganisms].neuron[numNeurons].gmaxca					= (const string*)(*neuron_child).child("GMaxCa").text().get();
			organism[numOrganisms].neuron[numNeurons].burstinitatbottom			= (const string*)(*neuron_child).child("BurstInitAtBottom").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_id				= (const string*)(*neuron_child).child("CaActivation").child("ID").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_midpoint			= (const string*)(*neuron_child).child("CaActivation").child("MidPoint").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_slope			= (const string*)(*neuron_child).child("CaActivation").child("Slope").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_timeconst		= (const string*)(*neuron_child).child("CaActivation").child("TimeConstant").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_activatetype		= (const string*)(*neuron_child).child("CaActivation").child("ActivationType").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_id				= (const string*)(*neuron_child).child("CaDeactivation").child("ID").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_midpoint		= (const string*)(*neuron_child).child("CaDeactivation").child("MidPoint").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_slope			= (const string*)(*neuron_child).child("CaDeactivation").child("Slope").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_timeconst		= (const string*)(*neuron_child).child("CaDeactivation").child("TimeConstant").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_activatetype	= (const string*)(*neuron_child).child("CaDeactivation").child("ActivationType").text().get();
			numNeurons++;
		}
		cout << "total number of neurons: " << numNeurons << endl;

		/*************************************************************************************************************************************\
		|
		|		Synapse Section - Spiking / Non-spiking / Electrical
		|			**The spiking and electrical synapses have been commented out because we are not utilizing them in Rev.A.1.
		\*************************************************************************************************************************************/
		// Synapse Node
		pugi::xml_node Synapses = neuralModule.child("Synapse");

		//	Non-Spiking Synapses
		pugi::xml_object_range<pugi::xml_node_iterator> synapselist_nonspiking = Synapses.child("NonSpikingSynapses").child("SynapseType").children();
		unsigned int numNonSpikeSynapses = 0;
		for (synapsenospike_child = synapselist_nonspiking.begin(); synapsenospike_child != synapselist_nonspiking.end(); synapsenospike_child++){
			/*
			cout << "Name: "		<< (*synapsenospike_child).child("Name").child_value()		<< endl;
			cout << "\tID: "		<< (*synapsenospike_child).child("ID").child_value()		<< endl;
			cout << "\tType: "		<< (*synapsenospike_child).child("Type").child_value()		<< endl;
			cout << "\tEquil: "		<< (*synapsenospike_child).child("Equil").child_value()		<< endl;
			cout << "\tSynAmp: "	<< (*synapsenospike_child).child("SynAmp").child_value()	<< endl;
			cout << "\tSat. V: "	<< (*synapsenospike_child).child("SaturateV").child_value()	<< endl;
			cout << "}" << endl;
			*/
			organism[numOrganisms].synapse[numNonSpikeSynapses].name		= (const string*)(*synapsenospike_child).child("Name").text().get();
			organism[numOrganisms].synapse[numNonSpikeSynapses].id			= (const string*)(*synapsenospike_child).child("ID").text().get();
			organism[numOrganisms].synapse[numNonSpikeSynapses].type		= (const string*)(*synapsenospike_child).child("Type").text().get();
			organism[numOrganisms].synapse[numNonSpikeSynapses].equil		= (const string*)(*synapsenospike_child).child("Equil").text().get();
			organism[numOrganisms].synapse[numNonSpikeSynapses].synamp		= (const string*)(*synapsenospike_child).child("SynAmp").text().get();
			organism[numOrganisms].synapse[numNonSpikeSynapses].saturatev	= (const string*)(*synapsenospike_child).child("SaturateV").text().get();
			numNonSpikeSynapses++;
		}
		//cout << "total number of nonspiking synapses: " << numNonSpikeSynapses << endl;
		
		/*//	Skiping Synpases
		pugi::xml_object_range<pugi::xml_node_iterator> synapselist_spiking = Synapses.child("SpikingSynapses").child("SynapseType").children();
		unsigned int numSpikeSynapses = 0;
		for (synapsespike_child = synapselist_spiking.begin(); synapsespike_child != synapselist_spiking.end(); synapsespike_child++){
			cout << "Name: "			<< (*synapsespike_child).child("Name").child_value()			<< endl;
			cout << "\tID: "			<< (*synapsespike_child).child("ID").child_value()				<< endl;
			cout << "\tType: "			<< (*synapsespike_child).child("Type").child_value()			<< endl;
			cout << "\tEquil: "			<< (*synapsespike_child).child("Equil").child_value()			<< endl;
			cout << "\tSyn Amp: "		<< (*synapsespike_child).child("SynAmp").child_value()			<< endl;
			cout << "\tDecay: "			<< (*synapsespike_child).child("Decay").child_value()			<< endl;
			cout << "\tRel Facil: "		<< (*synapsespike_child).child("RelFacil").child_value()		<< endl;
			cout << "\tFacil Decay: "	<< (*synapsespike_child).child("FacilDecay").child_value()		<< endl;
			cout << "\tVolt Dep: "		<< (*synapsespike_child).child("VoltDep").child_value()			<< endl;
			cout << "\tMax Rel Cond: "	<< (*synapsespike_child).child("MaxRelCond").child_value()		<< endl;
			cout << "\tSat PS Pot: "	<< (*synapsespike_child).child("SatPSPot").child_value()		<< endl;
			cout << "\tThresh PS Pot: "	<< (*synapsespike_child).child("ThreshPSPot").child_value()		<< endl;
			cout << "\tHebbian: "		<< (*synapsespike_child).child("Hebbian").child_value()			<< endl;
			cout << "\tMax Aug Cond: "	<< (*synapsespike_child).child("MaxAugCond").child_value()		<< endl;
			cout << "\tLearning Inc: "	<< (*synapsespike_child).child("LearningInc").child_value()		<< endl;
			cout << "\tLearning Time: "	<< (*synapsespike_child).child("LearningTime").child_value()	<< endl;
			cout << "\tAllow Forget: "	<< (*synapsespike_child).child("AllowForget").child_value()		<< endl;
			cout << "\tForget Time: "	<< (*synapsespike_child).child("ForgetTime").child_value()		<< endl;
			cout << "\tConsolidation: "	<< (*synapsespike_child).child("Consolidation").child_value()	<< endl;
			numSpikeSynapses++;
		}
		cout << "total number of spiking synapses: " << numSpikeSynapses << endl;
		
		//	Electrical Synpases
		pugi::xml_object_range<pugi::xml_node_iterator> synapselist_elec = Synapses.child("ElectricalSynapses").child("SynapseType").children();
		
		unsigned int numElectricalSynapses = 0;
		for (synapseelec_child = synapselist_elec.begin(); synapseelec_child != synapselist_elec.end(); synapseelec_child++){
			cout << "Name: "		<< (*synapseelec_child).child("Name").child_value()			<< endl;
			cout << "\tID: "			<< (*synapseelec_child).child("ID").child_value()			<< endl;
			cout << "\tType: "		<< (*synapseelec_child).child("Type").child_value()			<< endl;
			cout << "\tLow Coup: "	<< (*synapseelec_child).child("LowCoup").child_value()		<< endl;
			cout << "\tHi Coup: "		<< (*synapseelec_child).child("HiCoup").child_value()		<< endl;
			cout << "\tTurn On V: "	<< (*synapseelec_child).child("TurnOnV").child_value()		<< endl;
			cout << "\tSat. V: "		<< (*synapseelec_child).child("SaturateV").child_value()	<< endl;
			cout << "}" << endl;
			numElectricalSynapses++;
		}
		cout << "total number of electrical synapses: " << numElectricalSynapses << endl;
		*/

		/*************************************************************************************************************************************\
		|
		|		Connexion Section
		|
		\*************************************************************************************************************************************/
		pugi::xml_object_range<pugi::xml_node_iterator> connecionlist = neuralModule.child("Connexions").children();
		unsigned int numConnexions = 0;
		for (connexion_child = connecionlist.begin(); connexion_child != connecionlist.end(); connexion_child++){
			/*
			cout << "Name: "		<< (*synapsenospike_child).child("Name").child_value()		<< endl;
			cout << "\tID: "		<< (*synapsenospike_child).child("ID").child_value()		<< endl;
			cout << "\tType: "		<< (*synapsenospike_child).child("Type").child_value()		<< endl;
			cout << "\tEquil: "		<< (*synapsenospike_child).child("Equil").child_value()		<< endl;
			cout << "\tSynAmp: "	<< (*synapsenospike_child).child("SynAmp").child_value()	<< endl;
			cout << "\tSat. V: "	<< (*synapsenospike_child).child("SaturateV").child_value()	<< endl;
			cout << "}" << endl;
			*/
			organism[numOrganisms].connexion[numConnexions].id				= (const string*)(*connexion_child).child("ID").text().get();
			organism[numOrganisms].connexion[numConnexions].sourceid		= (const string*)(*connexion_child).child("SourceID").text().get();
			organism[numOrganisms].connexion[numConnexions].targetid		= (const string*)(*connexion_child).child("TargetID").text().get();
			organism[numOrganisms].connexion[numConnexions].type			= (const string*)(*connexion_child).child("Type").text().get();
			organism[numOrganisms].connexion[numConnexions].synapsetypeid	= (const string*)(*connexion_child).child("SynapseTypeID").text().get();
			organism[numOrganisms].connexion[numConnexions].delay			= (const string*)(*connexion_child).child("Delay").text().get();
			organism[numOrganisms].connexion[numConnexions].g				= (const string*)(*connexion_child).child("G").text().get();
			numNonSpikeSynapses++;
		}
		//cout << "total number of connexions: " << numConnexions << endl;

	}


	do {
		cout << "Press 'e' to exit: " ;
		cin >> exit;
		if (exit == 'e' || exit == 'E'){
			exit = 1;
		}
	} while (exit != 1);

	return 0;
}
