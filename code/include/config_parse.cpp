using namespace std;

//	Standard libraries
#include <vector>
#include <sstream>
#include <iostream>
//	Non-Standard libraries
#include "pugixml.hpp"
#include "error_handler.hpp"

void printVect(vector<string>const& vect)

typedef struct {
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
} SynapsesNonSpiking;

typedef struct {
	const string* name;
	const string* id;
	const string* type;
	const string* equil;
	const string* synamp;
	const string* decay;
	const string* relfacil;
	const string* facildecay;
	const string* voltdep;
	const string* maxrelcond;
	const string* satpspot;
	const string* threshpspot;
	const string* hebbian;
	const string* maxaugcond;
	const string* learninginc;
	const string* learningtime;
	const string* allowforget;
	const string* forgettime;
	const string* consolidation;
} SynapsesSpiking;

typedef struct {
	const string* name;
	const string* id;
	const string* type;
	const string* lowcoup;
	const string* hicoup;
	const string* turnonv;
	const string* saturatev;
} SynapsesElectrical;

typedef struct {
	const string* id;
	const string* sourceid;
	const string* targetid;
	const string* type;
	const string* synapsetypeid;
	const string* delay;
	const string* g;
} Connexions;

typedef struct{

	const string* organism_id;
	const string* organism_name;
	const string* neuralmodule_id;
	const string* neuralmodule_name;

	std::vector<Neurons>			neuron;
	std::vector<Connexions>			connexion;
	std::vector<SynapsesSpiking>	synapse_spiking;
	std::vector<SynapsesElectrical> synapse_electrical;
	std::vector<SynapsesNonSpiking> synapse_nonspiking;

} Organisms;


int main(int argc, char** argv) {
/*****************************************************************\
|		Identifiers and declarations -
\*****************************************************************/
	//	Identifiers to the specific struct vectors
	Organisms				orgis;
	Neurons					neurs;
	Connexions				conxs;
	SynapsesSpiking			synspk;
	SynapsesElectrical		synelec;
	SynapsesNonSpiking		synnonspk;

	//	Vector of organism sturct
	std::vector<Organisms>	organism;

	//	Declare vector of organism structs
	pugi::xml_node_iterator	organism_child;

	//	Declare vector of neuronal structs
	pugi::xml_node_iterator neuron_child;

	//	Declare vector of copnnexion structs
	pugi::xml_node_iterator connexion_child;

	//	Synapse Nodes (3 types: Spiking, Non-Spiking, Electrical)
	pugi::xml_node_iterator synapse_elec_child;
	pugi::xml_node_iterator synapse_spiking_child;
	pugi::xml_node_iterator synapse_nonspiking_child;

/*****************************************************************\
|		Variables -
\*****************************************************************/
	char exit = 0;

/*****************************************************************\
|		File load and validate section -
\*****************************************************************/

	const char* filepath = "test_file.asim";

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filepath);

	if (!result){
		error_handler(ERROR_FILE_LOAD);
	}

	cout << "File " << filepath << " Loaded Sucessfully " << endl << endl;

	/*****************************************************************\
	|		Organism declaration and path setup -
	\*****************************************************************/
	//	Set parent node to start traversing file from
	pugi::xml_node organism_parent = doc.child("Simulation").child("Environment").child("Organisms");

	//	Create array object for the iteration and struct array
	pugi::xml_object_range<pugi::xml_node_iterator> organismlist = organism_parent.children();

	//	Generate organim counter for length of vector of structs
	unsigned int numOrganisms = 0;

	//	Generate for loop to store organism in each
	for (organism_child = organismlist.begin(); organism_child != organismlist.end(); organism_child++)
	{
		//	Push back new organism created with default constructor
		organism.push_back(orgis);

		/**********************************************************************************************************************************************************\
		|
		|	Organism Section -
		|
		\**********************************************************************************************************************************************************/
		organism[numOrganisms].organism_name	= (const string*)organism_parent.child("Organsim").child("Name").text().get();
		organism[numOrganisms].organism_id		= (const string*)organism_parent.child("Organsim").child("ID").text().get();
		/*
		cout << "\tll:\t" << (const string*)organism_parent.child("Organsim").child("Name").text().get() << endl;
		cout << "\t" << &organism[numOrganisms].organism_name << endl;
		*/
		pugi::xml_node neuralModule = (*organism_child).child("NervousSystem").child("NeuralModules").child("NeuralModule");

		/**********************************************************************************************************************************************************\
		|
		|		Neuron Section -
		|
		\**********************************************************************************************************************************************************/
		//	Set a list to be generated on the neuron identified by the "Neurons.Neuron" name in the xml config file
		pugi::xml_object_range<pugi::xml_node_iterator> neuronlist = neuralModule.child("Neurons").children();

		//	Generate neuron counter for length of vector of structs
		unsigned int numNeurons = 0;

		//	Generate for loop to store neurons in each organism
		for (neuron_child = neuronlist.begin(); neuron_child != neuronlist.end(); neuron_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].neuron.push_back(neurs);

			//	Load data to struct vector
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

		/**********************************************************************************************************************************************************\
		|
		|		Synapse Section - Spiking / Non-spiking / Electrical
		|			**The spiking and electrical synapses have been commented out because we are not utilizing them in Rev.A.1.
		|
		\**********************************************************************************************************************************************************/
		// Synapse node to be used accross all 3 synapse types
		pugi::xml_node Synapses = neuralModule.child("Synapses");

		/**********************************************************************************************************************************************************\
		|***************************************************************	Spiking Synapses		***************************************************************|
		\**********************************************************************************************************************************************************/
		//	Child of the synapse, spiking or otherwise -> SynapseType
		pugi::xml_object_range<pugi::xml_node_iterator> synapse_spiking_list = Synapses.child("SpikingSynapses").children();

		//	Generate spiking synapse counter for length of vector of structs
		unsigned int numSpikingSynapses = 0;

		//	generate for loop to store neuronal spiking synapse in each organism
		for (synapse_spiking_child = synapse_spiking_list.begin(); synapse_spiking_child != synapse_spiking_list.end(); synapse_spiking_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].synapse_spiking.push_back(synspk);

			/*
			cout << "Name: "			<< (*synapse_spiking_child).child("Name").child_value()				<< endl;
			cout << "\tID: "			<< (*synapse_spiking_child).child("ID").child_value()				<< endl;
			cout << "\tType: "			<< (*synapse_spiking_child).child("Type").child_value()				<< endl;
			cout << "\tEquil: "			<< (*synapse_spiking_child).child("Equil").child_value()			<< endl;
			cout << "\tSyn Amp: "		<< (*synapse_spiking_child).child("SynAmp").child_value()			<< endl;
			cout << "\tDecay: "			<< (*synapse_spiking_child).child("Decay").child_value()			<< endl;
			cout << "\tRel Facil: "		<< (*synapse_spiking_child).child("RelFacil").child_value()			<< endl;
			cout << "\tFacil Decay: "	<< (*synapse_spiking_child).child("FacilDecay").child_value()		<< endl;
			cout << "\tVolt Dep: "		<< (*synapse_spiking_child).child("VoltDep").child_value()			<< endl;
			cout << "\tMax Rel Cond: "	<< (*synapse_spiking_child).child("MaxRelCond").child_value()		<< endl;
			cout << "\tSat PS Pot: "	<< (*synapse_spiking_child).child("SatPSPot").child_value()			<< endl;
			cout << "\tThresh PS Pot: "	<< (*synapse_spiking_child).child("ThreshPSPot").child_value()		<< endl;
			cout << "\tHebbian: "		<< (*synapse_spiking_child).child("Hebbian").child_value()			<< endl;
			cout << "\tMax Aug Cond: "	<< (*synapse_spiking_child).child("MaxAugCond").child_value()		<< endl;
			cout << "\tLearning Inc: "	<< (*synapse_spiking_child).child("LearningInc").child_value()		<< endl;
			cout << "\tLearning Time: "	<< (*synapse_spiking_child).child("LearningTime").child_value()		<< endl;
			cout << "\tAllow Forget: "	<< (*synapse_spiking_child).child("AllowForget").child_value()		<< endl;
			cout << "\tForget Time: "	<< (*synapse_spiking_child).child("ForgetTime").child_value()		<< endl;
			cout << "\tConsolidation: "	<< (*synapse_spiking_child).child("Consolidation").child_value()	<< endl;
			*/

			organism[numOrganisms].synapse_spiking[numSpikingSynapses].name				= (const string*)(*synapse_spiking_child).child("Name").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].id				= (const string*)(*synapse_spiking_child).child("ID").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].type				= (const string*)(*synapse_spiking_child).child("Type").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].equil			= (const string*)(*synapse_spiking_child).child("Equil").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].synamp			= (const string*)(*synapse_spiking_child).child("SynAmp").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].decay			= (const string*)(*synapse_spiking_child).child("Decay").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].relfacil			= (const string*)(*synapse_spiking_child).child("RelFacil").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].facildecay		= (const string*)(*synapse_spiking_child).child("FacilDecay").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].voltdep			= (const string*)(*synapse_spiking_child).child("VoltDep").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].maxrelcond		= (const string*)(*synapse_spiking_child).child("MaxRelCond").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].satpspot			= (const string*)(*synapse_spiking_child).child("SatPSPot").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].threshpspot		= (const string*)(*synapse_spiking_child).child("ThreshPSPot").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].hebbian			= (const string*)(*synapse_spiking_child).child("Hebbian").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].maxaugcond		= (const string*)(*synapse_spiking_child).child("MaxAugCond").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].learninginc		= (const string*)(*synapse_spiking_child).child("LearningInc").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].learningtime		= (const string*)(*synapse_spiking_child).child("LearningTime").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].allowforget		= (const string*)(*synapse_spiking_child).child("AllowForget").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].forgettime		= (const string*)(*synapse_spiking_child).child("ForgetTime").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].consolidation	= (const string*)(*synapse_spiking_child).child("Consolidation").text().get();

			numSpikingSynapses++;
		}
		cout << "total number of spiking synapses: " << numSpikingSynapses << endl;

		/**********************************************************************************************************************************************************\
		|***************************************************************	Non-Spiking Synapses	***************************************************************|
		\**********************************************************************************************************************************************************/
		pugi::xml_object_range<pugi::xml_node_iterator> synapse_nonspiking_list = Synapses.child("NonSpikingSynapses").children();

		//	Generate nonspiking synapse counter for length of vector of structs
		unsigned int numNonSpikeSynapses = 0;

		//	Generate for loop to store neuronal nonspiking in each organism
		for (synapse_nonspiking_child = synapse_nonspiking_list.begin(); synapse_nonspiking_child != synapse_nonspiking_list.end(); synapse_nonspiking_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].synapse_nonspiking.push_back(synnonspk);

			/*
			cout << "Name: "		<< (*synapse_nonspiking_child).child("Name").child_value()		<< endl;
			cout << "\tID: "		<< (*synapse_nonspiking_child).child("ID").child_value()		<< endl;
			cout << "\tType: "		<< (*synapse_nonspiking_child).child("Type").child_value()		<< endl;
			cout << "\tEquil: "		<< (*synapse_nonspiking_child).child("Equil").child_value()		<< endl;
			cout << "\tSynAmp: "	<< (*synapse_nonspiking_child).child("SynAmp").child_value()	<< endl;
			cout << "\tSat. V: "	<< (*synapse_nonspiking_child).child("SaturateV").child_value()	<< endl;
			*/

			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].name			= (const string*)(*synapse_nonspiking_child).child("Name").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].id			= (const string*)(*synapse_nonspiking_child).child("ID").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].type			= (const string*)(*synapse_nonspiking_child).child("Type").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].equil		= (const string*)(*synapse_nonspiking_child).child("Equil").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].synamp		= (const string*)(*synapse_nonspiking_child).child("SynAmp").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].saturatev	= (const string*)(*synapse_nonspiking_child).child("SaturateV").text().get();
			numNonSpikeSynapses++;
		}
		cout << "total number of nonspiking synapses: " << numNonSpikeSynapses << endl;

		/**********************************************************************************************************************************************************\
		|***************************************************************	Electrical Synapses		***************************************************************|
		\**********************************************************************************************************************************************************/
		pugi::xml_object_range<pugi::xml_node_iterator> synapse_elec_list = Synapses.child("ElectricalSynapses").children();

		//	Generate electrical synapse counter for length of vector of structs
		unsigned int numElectricalSynapses = 0;

		//	Generate for loop to store neuronal electrical synapse in each organism
		for (synapse_elec_child = synapse_elec_list.begin(); synapse_elec_child != synapse_elec_list.end(); synapse_elec_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].synapse_electrical.push_back(synelec);

			/*
			cout << "Name: "		<< (*synapse_elec_child).child("Name").child_value()		<< endl;
			cout << "\tID: "		<< (*synapse_elec_child).child("ID").child_value()			<< endl;
			cout << "\tType: "		<< (*synapse_elec_child).child("Type").child_value()		<< endl;
			cout << "\tLow Coup: "	<< (*synapse_elec_child).child("LowCoup").child_value()		<< endl;
			cout << "\tHi Coup: "	<< (*synapse_elec_child).child("HiCoup").child_value()		<< endl;
			cout << "\tTurn On V: "	<< (*synapse_elec_child).child("TurnOnV").child_value()		<< endl;
			cout << "\tSat. V: "	<< (*synapse_elec_child).child("SaturateV").child_value()	<< endl;
			*/

			organism[numOrganisms].synapse_electrical[numElectricalSynapses].name		= (const string*)(*synapse_elec_child).child("Name").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].id			= (const string*)(*synapse_elec_child).child("ID").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].type		= (const string*)(*synapse_elec_child).child("Type").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].lowcoup	= (const string*)(*synapse_elec_child).child("LowCoup").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].hicoup		= (const string*)(*synapse_elec_child).child("HiCoup").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].turnonv	= (const string*)(*synapse_elec_child).child("TurnOnV").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].saturatev	= (const string*)(*synapse_elec_child).child("SaturateV").text().get();

			numElectricalSynapses++;
		}
		cout << "total number of electrical synapses: " << numElectricalSynapses << endl;

		/*************************************************************************************************************************************\
		|
		|		Connexion Section -
		|
		\*************************************************************************************************************************************/
		//	Connexion node to identify each individual instance
		pugi::xml_object_range<pugi::xml_node_iterator> connexion_list = neuralModule.child("Connexions").children();

		//	Generate connexion counter for length of vector of structs
		unsigned int numConnexions = 0;

		//	Generate for loop to store neuronal connexions in each organism
		for (connexion_child = connexion_list.begin(); connexion_child != connexion_list.end(); connexion_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].connexion.push_back(conxs);

			/*
			cout << "Name: "		<< (*connexion_child).child("Name").child_value()		<< endl;
			cout << "\tID: "		<< (*connexion_child).child("ID").child_value()			<< endl;
			cout << "\tType: "		<< (*connexion_child).child("Type").child_value()		<< endl;
			cout << "\tEquil: "		<< (*connexion_child).child("Equil").child_value()		<< endl;
			cout << "\tSynAmp: "	<< (*connexion_child).child("SynAmp").child_value()		<< endl;
			cout << "\tSat. V: "	<< (*connexion_child).child("SaturateV").child_value()	<< endl;
			*/

			organism[numOrganisms].connexion[numConnexions].id				= (const string*)(*connexion_child).child("ID").text().get();
			organism[numOrganisms].connexion[numConnexions].sourceid		= (const string*)(*connexion_child).child("SourceID").text().get();
			organism[numOrganisms].connexion[numConnexions].targetid		= (const string*)(*connexion_child).child("TargetID").text().get();
			organism[numOrganisms].connexion[numConnexions].type			= (const string*)(*connexion_child).child("Type").text().get();
			organism[numOrganisms].connexion[numConnexions].synapsetypeid	= (const string*)(*connexion_child).child("SynapseTypeID").text().get();
			organism[numOrganisms].connexion[numConnexions].delay			= (const string*)(*connexion_child).child("Delay").text().get();
			organism[numOrganisms].connexion[numConnexions].g				= (const string*)(*connexion_child).child("G").text().get();

			numConnexions++;
		}

		//	Test the size of the found loaded connexions
		if (organism[numOrganisms].connexion.size() != numConnexions){
			error_handler(WARNING_CONNEXION_SIZE_MISMATCH);
		}

		//	Print the size of the vector of struct
		cout << endl << "Connexion list of size " << organism[numOrganisms].connexion.size() << " found." << endl;
		cout << "Elements found and loaded: " << endl;

		//	Print the elements
		for (int i = 0, size = organism[numOrganisms].connexion.size(); i < size; ++i){
			cout << "\tID\t\t"				<< &organism[numOrganisms].connexion[i].id				<< endl;
			cout << "\tSource ID\t"			<< &organism[numOrganisms].connexion[i].sourceid		<< endl;
			cout << "\tTarget ID\t"			<< &organism[numOrganisms].connexion[i].targetid		<< endl;
			cout << "\tType\t\t"			<< &organism[numOrganisms].connexion[i].type			<< endl;
			cout << "\tSynapse Type ID\t"	<< &organism[numOrganisms].connexion[i].synapsetypeid	<< endl;
			cout << "\tDelay\t\t"			<< &organism[numOrganisms].connexion[i].delay			<< endl;
			cout << "\tG\t\t"				<< &organism[numOrganisms].connexion[i].g				<< endl;
			cout << "	" << endl;
		}
	}

	/**************************************************************************************\
	|		exit if user has time to read and validate stored data / printed data
	\**************************************************************************************/
	do {
		cout << "Press 'e' to exit: ";
		cin >> exit;
		if (exit == 'e' || exit == 'E'){
			exit = 1;
		}
	} while (exit != 1);

	return 0;
}

/*************************************************************************************************************************************\
|
|		Print vector elements -
|			print a loaded vector element by element
|			expecting the input to be a vector of structs of vector of structs
|
\*************************************************************************************************************************************/

void printVect(vector<string>const& vect) {
	//	Check if the loaded vector is empty or has element
	if (vect.empty()){
		cout << "The vector loaded is empty." << endl;
		return;
	}

	//	Print the found elements
	for (int i = 0, size = vect.size(); i < size; ++i){
		cout << "organism name:\t"	<< &vect[i] << endl;
		cout << "organism id:\t"	<< &vect[i] << endl;
	}
}
