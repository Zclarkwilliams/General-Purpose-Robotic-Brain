//using namespace std;

//	Standard libraries
#include <vector>
#include <sstream>
#include <iostream>
//	Non-Standard libraries
#include "pugixml.hpp"
//#include "error_handler.hpp"

#include "model_config_data.hpp"

void printVect(std::vector<std::string>const& vect);

int NeuralModel::parse_model_config(char* file_path) {
//int main(int argc, const char* argv[]){
/*****************************************************************\
|		Identifiers and declarations -
\*****************************************************************/
	//	Identifiers to the specific struct vectors
	/*
	NeuralModel.Organisms				orgis;
	NeuralModel.Neurons					neurs;
	NeuralModel.Connexions				conxs;
	NeuralModel.SynapsesSpiking			synspk;
	NeuralModel.SynapsesElectrical		synelec;
	NeuralModel.SynapsesNonSpiking		synnonspk;
	*/
	NeuralModel* neuralmodel;
	//neuralmodel.organismVector orgVect;
	//	Vector of organism sturct
	//std::vector<neuralmodel.organism>	organism;


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

	const char* filepath = "C:\\Users\\Zachary\\Documents\\A_School\\URMP\\code\\include\\InvertedPendulum_mscfbk_09__17_Standalone.asim"; //= file_path;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filepath);

	if (!result){
		//error_handler(ERROR_FILE_LOAD);
		std::cout << "File " << filepath << " empty. Please fix path and try again." << std::endl << std::endl;
		return 1;
	}

	std::cout << "File " << filepath << " Loaded Sucessfully " << std::endl << std::endl;

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
		/**********************************************************************************************************************************************************\
		|
		|	Organism Section -
		|
		\**********************************************************************************************************************************************************/
		
		//std::make_unique<neuralmodel.organismStruct>() orgstructtemp;

		neuralmodel->organismStruct->organism_name	= (const std::string*)organism_parent.child("Organsim").child("Name").text().get();
		neuralmodel->organismStruct->organism_id	= (const std::string*)organism_parent.child("Organsim").child("ID").text().get();
		/*
		neuralmodel.organismStruct->organism_name	= (const std::string*)organism_parent.child("Organsim").child("Name").text().get();
		neuralmodel.organismStruct->organism_id	= (const std::string*)organism_parent.child("Organsim").child("ID").text().get();
		neuralmodel.organismStruct[numOrganisms].organism_name	= (const std::string*)organism_parent.child("Organsim").child("Name").text().get();
		neuralmodel.organismStruct[numOrganisms].organism_id	= (const std::string*)organism_parent.child("Organsim").child("ID").text().get();
		std::cout << "\tll:\t" << (const std::string*)organism_parent.child("Organsim").child("Name").text().get() << std::endl;
		std::cout << "\t" << &organism[numOrganisms].organism_name << std::endl;
		*/

		std::cout << "\tfound organism name:\t" << (const std::string*)organism_parent.child("Organsim").child("Name").text().get() << std::endl;
		std::cout << "\tstored organism name:\t" << neuralmodel->organismStruct->organism_name << std::endl;

		//	Push back new organism created with default constructor
		//neuralmodel->organismVector.push_back(orgstructtemp);
		neuralmodel->organismVector.push_back(std::make_shared<neuralmodel->organismStruct>());

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
		/*
		//	Generate for loop to store neurons in each organism
		for (neuron_child = neuronlist.begin(); neuron_child != neuronlist.end(); neuron_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].neuron.push_back(neurs);

			//	Load data to struct vector
			organism[numOrganisms].neuron[numNeurons].name						= (const std::string*)(*neuron_child).child("Name").text().get();
			organism[numOrganisms].neuron[numNeurons].id						= (const std::string*)(*neuron_child).child("ID").text().get();
			organism[numOrganisms].neuron[numNeurons].enabled					= (const std::string*)(*neuron_child).child("Enabled").text().get();
			organism[numOrganisms].neuron[numNeurons].tonicstimulus				= (const std::string*)(*neuron_child).child("TonicStimulus").text().get();
			organism[numOrganisms].neuron[numNeurons].noise						= (const std::string*)(*neuron_child).child("Noise").text().get();
			organism[numOrganisms].neuron[numNeurons].restingpot				= (const std::string*)(*neuron_child).child("RestingPot").text().get();
			organism[numOrganisms].neuron[numNeurons].size						= (const std::string*)(*neuron_child).child("Size").text().get();
			organism[numOrganisms].neuron[numNeurons].timeconst					= (const std::string*)(*neuron_child).child("TimeConst").text().get();
			organism[numOrganisms].neuron[numNeurons].initthresh				= (const std::string*)(*neuron_child).child("InitialThresh").text().get();
			organism[numOrganisms].neuron[numNeurons].relativeaccom				= (const std::string*)(*neuron_child).child("RelativeAccom").text().get();
			organism[numOrganisms].neuron[numNeurons].accomtimeconst			= (const std::string*)(*neuron_child).child("AccomTimeConst").text().get();
			organism[numOrganisms].neuron[numNeurons].ahpamp					= (const std::string*)(*neuron_child).child("AHPAmp").text().get();
			organism[numOrganisms].neuron[numNeurons].ahptimeconst				= (const std::string*)(*neuron_child).child("AHPTimeConst").text().get();
			organism[numOrganisms].neuron[numNeurons].gmaxca					= (const std::string*)(*neuron_child).child("GMaxCa").text().get();
			organism[numOrganisms].neuron[numNeurons].burstinitatbottom			= (const std::string*)(*neuron_child).child("BurstInitAtBottom").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_id				= (const std::string*)(*neuron_child).child("CaActivation").child("ID").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_midpoint			= (const std::string*)(*neuron_child).child("CaActivation").child("MidPoint").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_slope			= (const std::string*)(*neuron_child).child("CaActivation").child("Slope").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_timeconst		= (const std::string*)(*neuron_child).child("CaActivation").child("TimeConstant").text().get();
			organism[numOrganisms].neuron[numNeurons].caactive_activatetype		= (const std::string*)(*neuron_child).child("CaActivation").child("ActivationType").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_id				= (const std::string*)(*neuron_child).child("CaDeactivation").child("ID").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_midpoint		= (const std::string*)(*neuron_child).child("CaDeactivation").child("MidPoint").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_slope			= (const std::string*)(*neuron_child).child("CaDeactivation").child("Slope").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_timeconst		= (const std::string*)(*neuron_child).child("CaDeactivation").child("TimeConstant").text().get();
			organism[numOrganisms].neuron[numNeurons].cadeactive_activatetype	= (const std::string*)(*neuron_child).child("CaDeactivation").child("ActivationType").text().get();
			numNeurons++;
		}
		std::cout << "total number of neurons: " << numNeurons << std::endl;
*/
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
/*
		//	generate for loop to store neuronal spiking synapse in each organism
		for (synapse_spiking_child = synapse_spiking_list.begin(); synapse_spiking_child != synapse_spiking_list.end(); synapse_spiking_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].synapse_spiking.push_back(synspk);

			/*
			std::cout << "Name: "			<< (*synapse_spiking_child).child("Name").child_value()				<< std::endl;
			std::cout << "\tID: "			<< (*synapse_spiking_child).child("ID").child_value()				<< std::endl;
			std::cout << "\tType: "			<< (*synapse_spiking_child).child("Type").child_value()				<< std::endl;
			std::cout << "\tEquil: "			<< (*synapse_spiking_child).child("Equil").child_value()			<< std::endl;
			std::cout << "\tSyn Amp: "		<< (*synapse_spiking_child).child("SynAmp").child_value()			<< std::endl;
			std::cout << "\tDecay: "			<< (*synapse_spiking_child).child("Decay").child_value()			<< std::endl;
			std::cout << "\tRel Facil: "		<< (*synapse_spiking_child).child("RelFacil").child_value()			<< std::endl;
			std::cout << "\tFacil Decay: "	<< (*synapse_spiking_child).child("FacilDecay").child_value()		<< std::endl;
			std::cout << "\tVolt Dep: "		<< (*synapse_spiking_child).child("VoltDep").child_value()			<< std::endl;
			std::cout << "\tMax Rel Cond: "	<< (*synapse_spiking_child).child("MaxRelCond").child_value()		<< std::endl;
			std::cout << "\tSat PS Pot: "	<< (*synapse_spiking_child).child("SatPSPot").child_value()			<< std::endl;
			std::cout << "\tThresh PS Pot: "	<< (*synapse_spiking_child).child("ThreshPSPot").child_value()		<< std::endl;
			std::cout << "\tHebbian: "		<< (*synapse_spiking_child).child("Hebbian").child_value()			<< std::endl;
			std::cout << "\tMax Aug Cond: "	<< (*synapse_spiking_child).child("MaxAugCond").child_value()		<< std::endl;
			std::cout << "\tLearning Inc: "	<< (*synapse_spiking_child).child("LearningInc").child_value()		<< std::endl;
			std::cout << "\tLearning Time: "	<< (*synapse_spiking_child).child("LearningTime").child_value()		<< std::endl;
			std::cout << "\tAllow Forget: "	<< (*synapse_spiking_child).child("AllowForget").child_value()		<< std::endl;
			std::cout << "\tForget Time: "	<< (*synapse_spiking_child).child("ForgetTime").child_value()		<< std::endl;
			std::cout << "\tConsolidation: "	<< (*synapse_spiking_child).child("Consolidation").child_value()	<< std::endl;
			*/
/*
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].name				= (const std::string*)(*synapse_spiking_child).child("Name").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].id				= (const std::string*)(*synapse_spiking_child).child("ID").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].type				= (const std::string*)(*synapse_spiking_child).child("Type").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].equil			= (const std::string*)(*synapse_spiking_child).child("Equil").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].synamp			= (const std::string*)(*synapse_spiking_child).child("SynAmp").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].decay			= (const std::string*)(*synapse_spiking_child).child("Decay").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].relfacil			= (const std::string*)(*synapse_spiking_child).child("RelFacil").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].facildecay		= (const std::string*)(*synapse_spiking_child).child("FacilDecay").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].voltdep			= (const std::string*)(*synapse_spiking_child).child("VoltDep").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].maxrelcond		= (const std::string*)(*synapse_spiking_child).child("MaxRelCond").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].satpspot			= (const std::string*)(*synapse_spiking_child).child("SatPSPot").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].threshpspot		= (const std::string*)(*synapse_spiking_child).child("ThreshPSPot").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].hebbian			= (const std::string*)(*synapse_spiking_child).child("Hebbian").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].maxaugcond		= (const std::string*)(*synapse_spiking_child).child("MaxAugCond").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].learninginc		= (const std::string*)(*synapse_spiking_child).child("LearningInc").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].learningtime		= (const std::string*)(*synapse_spiking_child).child("LearningTime").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].allowforget		= (const std::string*)(*synapse_spiking_child).child("AllowForget").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].forgettime		= (const std::string*)(*synapse_spiking_child).child("ForgetTime").text().get();
			organism[numOrganisms].synapse_spiking[numSpikingSynapses].consolidation	= (const std::string*)(*synapse_spiking_child).child("Consolidation").text().get();

			numSpikingSynapses++;
		}
		std::cout << "total number of spiking synapses: " << numSpikingSynapses << std::endl;
*/
		/**********************************************************************************************************************************************************\
		|***************************************************************	Non-Spiking Synapses	***************************************************************|
		\**********************************************************************************************************************************************************/
		pugi::xml_object_range<pugi::xml_node_iterator> synapse_nonspiking_list = Synapses.child("NonSpikingSynapses").children();

		//	Generate nonspiking synapse counter for length of vector of structs
		unsigned int numNonSpikeSynapses = 0;
/*
		//	Generate for loop to store neuronal nonspiking in each organism
		for (synapse_nonspiking_child = synapse_nonspiking_list.begin(); synapse_nonspiking_child != synapse_nonspiking_list.end(); synapse_nonspiking_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].synapse_nonspiking.push_back(synnonspk);
*/
			/*
			std::cout << "Name: "		<< (*synapse_nonspiking_child).child("Name").child_value()		<< std::endl;
			std::cout << "\tID: "		<< (*synapse_nonspiking_child).child("ID").child_value()		<< std::endl;
			std::cout << "\tType: "		<< (*synapse_nonspiking_child).child("Type").child_value()		<< std::endl;
			std::cout << "\tEquil: "		<< (*synapse_nonspiking_child).child("Equil").child_value()		<< std::endl;
			std::cout << "\tSynAmp: "	<< (*synapse_nonspiking_child).child("SynAmp").child_value()	<< std::endl;
			std::cout << "\tSat. V: "	<< (*synapse_nonspiking_child).child("SaturateV").child_value()	<< std::endl;
			*/
/*
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].name			= (const std::string*)(*synapse_nonspiking_child).child("Name").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].id			= (const std::string*)(*synapse_nonspiking_child).child("ID").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].type			= (const std::string*)(*synapse_nonspiking_child).child("Type").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].equil		= (const std::string*)(*synapse_nonspiking_child).child("Equil").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].synamp		= (const std::string*)(*synapse_nonspiking_child).child("SynAmp").text().get();
			organism[numOrganisms].synapse_nonspiking[numNonSpikeSynapses].saturatev	= (const std::string*)(*synapse_nonspiking_child).child("SaturateV").text().get();
			numNonSpikeSynapses++;
		}
		std::cout << "total number of nonspiking synapses: " << numNonSpikeSynapses << std::endl;
*/
		/**********************************************************************************************************************************************************\
		|***************************************************************	Electrical Synapses		***************************************************************|
		\**********************************************************************************************************************************************************/
		pugi::xml_object_range<pugi::xml_node_iterator> synapse_elec_list = Synapses.child("ElectricalSynapses").children();

		//	Generate electrical synapse counter for length of vector of structs
		unsigned int numElectricalSynapses = 0;
/*
		//	Generate for loop to store neuronal electrical synapse in each organism
		for (synapse_elec_child = synapse_elec_list.begin(); synapse_elec_child != synapse_elec_list.end(); synapse_elec_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].synapse_electrical.push_back(synelec);
*/
			/*
			std::cout << "Name: "		<< (*synapse_elec_child).child("Name").child_value()		<< std::endl;
			std::cout << "\tID: "		<< (*synapse_elec_child).child("ID").child_value()			<< std::endl;
			std::cout << "\tType: "		<< (*synapse_elec_child).child("Type").child_value()		<< std::endl;
			std::cout << "\tLow Coup: "	<< (*synapse_elec_child).child("LowCoup").child_value()		<< std::endl;
			std::cout << "\tHi Coup: "	<< (*synapse_elec_child).child("HiCoup").child_value()		<< std::endl;
			std::cout << "\tTurn On V: "	<< (*synapse_elec_child).child("TurnOnV").child_value()		<< std::endl;
			std::cout << "\tSat. V: "	<< (*synapse_elec_child).child("SaturateV").child_value()	<< std::endl;
			*/
/*
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].name		= (const std::string*)(*synapse_elec_child).child("Name").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].id			= (const std::string*)(*synapse_elec_child).child("ID").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].type		= (const std::string*)(*synapse_elec_child).child("Type").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].lowcoup	= (const std::string*)(*synapse_elec_child).child("LowCoup").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].hicoup		= (const std::string*)(*synapse_elec_child).child("HiCoup").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].turnonv	= (const std::string*)(*synapse_elec_child).child("TurnOnV").text().get();
			organism[numOrganisms].synapse_electrical[numElectricalSynapses].saturatev	= (const std::string*)(*synapse_elec_child).child("SaturateV").text().get();

			numElectricalSynapses++;
		}
		std::cout << "total number of electrical synapses: " << numElectricalSynapses << std::endl;
*/
		/*************************************************************************************************************************************\
		|
		|		Connexion Section -
		|
		\*************************************************************************************************************************************/
		//	Connexion node to identify each individual instance
		pugi::xml_object_range<pugi::xml_node_iterator> connexion_list = neuralModule.child("Connexions").children();

		//	Generate connexion counter for length of vector of structs
		unsigned int numConnexions = 0;
/*
		//	Generate for loop to store neuronal connexions in each organism
		for (connexion_child = connexion_list.begin(); connexion_child != connexion_list.end(); connexion_child++){

			//	Make room for the new member struct by pushing the vector
			organism[numOrganisms].connexion.push_back(conxs);

			/*
			std::cout << "Name: "		<< (*connexion_child).child("Name").child_value()		<< std::endl;
			std::cout << "\tID: "		<< (*connexion_child).child("ID").child_value()			<< std::endl;
			std::cout << "\tType: "		<< (*connexion_child).child("Type").child_value()		<< std::endl;
			std::cout << "\tEquil: "		<< (*connexion_child).child("Equil").child_value()		<< std::endl;
			std::cout << "\tSynAmp: "	<< (*connexion_child).child("SynAmp").child_value()		<< std::endl;
			std::cout << "\tSat. V: "	<< (*connexion_child).child("SaturateV").child_value()	<< std::endl;
			*/
/*
			organism[numOrganisms].connexion[numConnexions].id				= (const std::string*)(*connexion_child).child("ID").text().get();
			organism[numOrganisms].connexion[numConnexions].sourceid		= (const std::string*)(*connexion_child).child("SourceID").text().get();
			organism[numOrganisms].connexion[numConnexions].targetid		= (const std::string*)(*connexion_child).child("TargetID").text().get();
			organism[numOrganisms].connexion[numConnexions].type			= (const std::string*)(*connexion_child).child("Type").text().get();
			organism[numOrganisms].connexion[numConnexions].synapsetypeid	= (const std::string*)(*connexion_child).child("SynapseTypeID").text().get();
			organism[numOrganisms].connexion[numConnexions].delay			= (const std::string*)(*connexion_child).child("Delay").text().get();
			organism[numOrganisms].connexion[numConnexions].g				= (const std::string*)(*connexion_child).child("G").text().get();

			numConnexions++;
		}

		//	Test the size of the found loaded connexions
		if (organism[numOrganisms].connexion.size() != numConnexions){
			//error_handler(WARNING_CONNEXION_SIZE_MISMATCH);
			std::cout << "ERROR: Connexion count mismatch. Number of connexions in file: " << organism[numOrganisms].connexion.size() << " number of connexions processed " << numConnexions << std::endl << std::endl;
			return 1;
		}
*/
		//	Print the size of the vector of struct
		//std::cout << std::endl << "Connexion list of size " << organism[numOrganisms].connexion.size() << " found." << std::endl;
		//std::cout << "Elements found and loaded: " << std::endl;

		/*
		//	Print the elements
		for (int i = 0, size = organism[numOrganisms].connexion.size(); i < size; ++i){
			std::cout << "\tID\t\t"				<< &organism[numOrganisms].connexion[i].id				<< std::endl;
			std::cout << "\tSource ID\t"			<< &organism[numOrganisms].connexion[i].sourceid		<< std::endl;
			std::cout << "\tTarget ID\t"			<< &organism[numOrganisms].connexion[i].targetid		<< std::endl;
			std::cout << "\tType\t\t"			<< &organism[numOrganisms].connexion[i].type			<< std::endl;
			std::cout << "\tSynapse Type ID\t"	<< &organism[numOrganisms].connexion[i].synapsetypeid	<< std::endl;
			std::cout << "\tDelay\t\t"			<< &organism[numOrganisms].connexion[i].delay			<< std::endl;
			std::cout << "\tG\t\t"				<< &organism[numOrganisms].connexion[i].g				<< std::endl;
			std::cout << "	" << std::endl;
		}
		std::cout << "Organism Size:" << organism.size() << std::endl;
		*/
	}
	
	/**************************************************************************************\
	|		exit if user has time to read and validate stored data / printed data
	\**************************************************************************************/
	do {
		std::cout << "Press 'e' to exit: ";
		std::cin >> exit;
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
/*
void printVect(std::vector<std::string>const& vect) {
	//	Check if the loaded vector is empty or has element
	if (vect.empty()){
		std::cout << "The vector loaded is empty." << std::endl;
		return;
	}

	//	Print the found elements
	for (int i = 0, size = vect.size(); i < size; ++i){
		std::cout << "organism name:\t"	<< &vect[i] << std::endl;
		std::cout << "organism id:\t"	<< &vect[i] << std::endl;
	}
}
*/