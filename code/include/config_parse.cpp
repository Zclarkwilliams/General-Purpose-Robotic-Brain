//using namespace std;

//	Standard libraries
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

//	Non-Standard libraries
#include "pugixml.hpp"

//	Custom made header files
//#include "error_handler.hpp"
#include "model_config_data.hpp"

int NeuralModel::parse_config_file() {
	/*****************************************************************\
	|		Identifiers and declarations -
	\*****************************************************************/
	//	Identifiers to the specific struct vectors
	/*	Creating the vector for the class and allocate the room for the vector.	*/
	std::shared_ptr<NeuralModel> neural_model = std::make_shared<NeuralModel>();
	
	// Instantiate the structs for each data set
	Neurons			neuronStruct;
	Connexions			connexionStruct;
	SynapsesSpiking		spikingStruct;
	SynapsesElectrical  electricalStruct;
	SynapsesNonSpiking	nonspikingStruct;
	Organisms		    organismStruct;
	
	// Instantiate and generate the organism vector struct
	std::vector<std::shared_ptr<Organisms>>	organismVector;
	//std::vector<std::shared_ptr<Organisms>>	organismVector;

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
	//char end = 0;
	const char * filePath;

	/*****************************************************************\
	|		File load and validate section -
	\*****************************************************************/
	
	NeuralModel::get_config_file_path();

	filePath = &configFilePath[0];

	pugi::xml_document doc;
	pugi::xml_parse_result open_result = doc.load_file(filePath);

	if (!open_result){
		//error_handler(ERROR_FILE_LOAD);
		std::cout << open_result.description() << filePath << " empty. Please fix path and try again." << std::endl;
		return 1;
	}

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
		//	Setup the parent to child path the depth of the config file we want to start aquiring data
		pugi::xml_node neuralModule = organism_child->child("NervousSystem").child("NeuralModules").child("NeuralModule");
		
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
		for (neuron_child = neuronlist.begin(); neuron_child != neuronlist.end(); neuron_child++) {
			//	Load data to struct
			neuronStruct.name						= (const std::string*)neuron_child->child("Name").text().get();
	/*		neuronStruct.id							= (const std::string*)neuron_child->child("ID").text().get();
			neuronStruct.enabled					= (const std::string*)neuron_child->child("Enabled").text().get();
			neuronStruct.tonicstimulus				= (const std::string*)neuron_child->child("TonicStimulus").text().get();
			neuronStruct.noise						= (const std::string*)neuron_child->child("Noise").text().get();
			neuronStruct.restingpot					= (const std::string*)neuron_child->child("RestingPot").text().get();
			neuronStruct.size						= (const std::string*)neuron_child->child("Size").text().get();
			neuronStruct.timeconst					= (const std::string*)neuron_child->child("TimeConst").text().get();
			neuronStruct.initthresh					= (const std::string*)neuron_child->child("InitialThresh").text().get();
			neuronStruct.relativeaccom				= (const std::string*)neuron_child->child("RelativeAccom").text().get();
			neuronStruct.accomtimeconst				= (const std::string*)neuron_child->child("AccomTimeConst").text().get();
			neuronStruct.ahpamp						= (const std::string*)neuron_child->child("AHPAmp").text().get();
			neuronStruct.ahptimeconst				= (const std::string*)neuron_child->child("AHPTimeConst").text().get();
			neuronStruct.gmaxca						= (const std::string*)neuron_child->child("GMaxCa").text().get();
			neuronStruct.burstinitatbottom			= (const std::string*)neuron_child->child("BurstInitAtBottom").text().get();
			neuronStruct.caactive_id				= (const std::string*)neuron_child->child("CaActivation").child("ID").text().get();
			neuronStruct.caactive_midpoint			= (const std::string*)neuron_child->child("CaActivation").child("MidPoint").text().get();
			neuronStruct.caactive_slope				= (const std::string*)neuron_child->child("CaActivation").child("Slope").text().get();
			neuronStruct.caactive_timeconst			= (const std::string*)neuron_child->child("CaActivation").child("TimeConstant").text().get();
			neuronStruct.caactive_activatetype		= (const std::string*)neuron_child->child("CaActivation").child("ActivationType").text().get();
			neuronStruct.cadeactive_id				= (const std::string*)neuron_child->child("CaDeactivation").child("ID").text().get();
			neuronStruct.cadeactive_midpoint		= (const std::string*)neuron_child->child("CaDeactivation").child("MidPoint").text().get();
			neuronStruct.cadeactive_slope			= (const std::string*)neuron_child->child("CaDeactivation").child("Slope").text().get();
			neuronStruct.cadeactive_timeconst		= (const std::string*)neuron_child->child("CaDeactivation").child("TimeConstant").text().get();
			neuronStruct.cadeactive_activatetype	= (const std::string*)neuron_child->child("CaDeactivation").child("ActivationType").text().get();
	*/
			//	Make room for the new member struct by pushing the vector
			organismStruct.neuronVector.emplace_back(std::make_shared<Neurons>(neuronStruct));
			
			// Increase neuron counter
			numNeurons++;
		}
		std::cout << "total number of neurons: " << numNeurons << std::endl;

		//	Check if the loaded vector is empty or has element
		if (organismStruct.neuronVector.empty()) {
			std::cout << "The vector loaded is empty." << std::endl;
			//error_handler(ERROR_NEURON_VECTOR_EMPTY);
			return 1;
		}
		else if (organismStruct.neuronVector.size() != numNeurons) {
			std::cout << "Neuron characteristic vector not same size as number of neurons counted in config file! Resolve and try again." << std::endl;
			//error_handler(ERROR_NEURON_VECTOR_SIZE_MISMATCH);
			return 1;
		}
		
		//	Print the found elements
		for (int i = 0, size = organismStruct.neuronVector.size(); i < size; ++i) {
			std::cout << "organism name:\t" << &organismStruct.neuronVector[i] << std::endl;
		}
		
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
		for (synapse_spiking_child = synapse_spiking_list.begin(); synapse_spiking_child != synapse_spiking_list.end(); synapse_spiking_child++) {
			// Load the spiking synapse values into a struct
			spikingStruct.name			= (const std::string*)synapse_spiking_child->child("Name").text().get();
			spikingStruct.id			= (const std::string*)synapse_spiking_child->child("ID").text().get();
			spikingStruct.type			= (const std::string*)synapse_spiking_child->child("Type").text().get();
			spikingStruct.equil			= (const std::string*)synapse_spiking_child->child("Equil").text().get();
			spikingStruct.synamp		= (const std::string*)synapse_spiking_child->child("SynAmp").text().get();
			spikingStruct.decay			= (const std::string*)synapse_spiking_child->child("Decay").text().get();
			spikingStruct.relfacil		= (const std::string*)synapse_spiking_child->child("RelFacil").text().get();
			spikingStruct.facildecay	= (const std::string*)synapse_spiking_child->child("FacilDecay").text().get();
			spikingStruct.voltdep		= (const std::string*)synapse_spiking_child->child("VoltDep").text().get();
			spikingStruct.maxrelcond	= (const std::string*)synapse_spiking_child->child("MaxRelCond").text().get();
			spikingStruct.satpspot		= (const std::string*)synapse_spiking_child->child("SatPSPot").text().get();
			spikingStruct.threshpspot	= (const std::string*)synapse_spiking_child->child("ThreshPSPot").text().get();
			spikingStruct.hebbian		= (const std::string*)synapse_spiking_child->child("Hebbian").text().get();
			spikingStruct.maxaugcond	= (const std::string*)synapse_spiking_child->child("MaxAugCond").text().get();
			spikingStruct.learninginc	= (const std::string*)synapse_spiking_child->child("LearningInc").text().get();
			spikingStruct.learningtime	= (const std::string*)synapse_spiking_child->child("LearningTime").text().get();
			spikingStruct.allowforget	= (const std::string*)synapse_spiking_child->child("AllowForget").text().get();
			spikingStruct.forgettime	= (const std::string*)synapse_spiking_child->child("ForgetTime").text().get();
			spikingStruct.consolidation	= (const std::string*)synapse_spiking_child->child("Consolidation").text().get();
			std::cout << spikingStruct.name << std::endl;
			//	Make room for the new member struct by pushing the vector
			organismStruct.spikingVector.emplace_back(spikingStruct);

			// Increase spiking synapse counter
			numSpikingSynapses++;
		}
		std::cout << "total number of spiking synapses: " << numSpikingSynapses << std::endl;

		//	Check if the loaded vector is empty or has element
		if (organismStruct.spikingVector.empty()) {
			std::cout << "The spiking synapse vector loaded is empty." << std::endl;
			//error_handler(ERROR_SPIKING_VECTOR_EMPTY);
			return 1;
		}
		else if (organismStruct.spikingVector.size() != numSpikingSynapses) {
			std::cout << "Spiking synapse characteristic vector size and number of spiking synapses from config file mismatch! Resolve and try again." << std::endl;
			//error_handler(ERROR_SPIKING_VECTOR_SIZE_MISMATCH);
			return 1;
		}

		//	Print the found elements
		for (int i = 0, size = organismStruct.spikingVector.size(); i < size; ++i) {
			std::cout << "spikingVector name:\t" << &organismStruct.spikingVector[i] << std::endl;
		}

		/**********************************************************************************************************************************************************\
		|***************************************************************	Non-Spiking Synapses	***************************************************************|
		\**********************************************************************************************************************************************************/
		pugi::xml_object_range<pugi::xml_node_iterator> synapse_nonspiking_list = Synapses.child("NonSpikingSynapses").children();

		//	Generate nonspiking synapse counter for length of vector of structs
		unsigned int numNonSpikeSynapses = 0;
		
		//	Generate for loop to store neuronal nonspiking in each organism
		for (synapse_nonspiking_child = synapse_nonspiking_list.begin(); synapse_nonspiking_child != synapse_nonspiking_list.end(); synapse_nonspiking_child++){
			// Load the non-spiking synapse values into the struct
			/*
			std::cout << "Name: "		<< synapse_nonspiking_child->child("Name").child_value()		<< std::endl;
			std::cout << "\tID: "		<< synapse_nonspiking_child->child("ID").child_value()		<< std::endl;
			std::cout << "\tType: "		<< synapse_nonspiking_child->child("Type").child_value()		<< std::endl;
			std::cout << "\tEquil: "		<< synapse_nonspiking_child->child("Equil").child_value()		<< std::endl;
			std::cout << "\tSynAmp: "	<< synapse_nonspiking_child->child("SynAmp").child_value()	<< std::endl;
			std::cout << "\tSat. V: "	<< synapse_nonspiking_child->child("SaturateV").child_value()	<< std::endl;
			*/
			nonspikingStruct.name		= (const std::string*)synapse_nonspiking_child->child("Name").text().get();
			nonspikingStruct.id			= (const std::string*)synapse_nonspiking_child->child("ID").text().get();
			nonspikingStruct.type		= (const std::string*)synapse_nonspiking_child->child("Type").text().get();
			nonspikingStruct.equil		= (const std::string*)synapse_nonspiking_child->child("Equil").text().get();
			nonspikingStruct.synamp		= (const std::string*)synapse_nonspiking_child->child("SynAmp").text().get();
			nonspikingStruct.saturatev	= (const std::string*)synapse_nonspiking_child->child("SaturateV").text().get();

			//	Make room for the new member struct by pushing the vector
			organismStruct.nonspikingVector.emplace_back(nonspikingStruct);

			// Increase spiking synapse counter
			numNonSpikeSynapses++;
		}
		std::cout << "total number of non-spiking synapses: " << numNonSpikeSynapses << std::endl;

		//	Check if the loaded vector is empty or has element
		if (organismStruct.nonspikingVector.empty()) {
			std::cout << "The non-spiking synapse vector loaded is empty." << std::endl;
			//error_handler(ERROR_NONSPIKING_VECTOR_EMPTY);
			return 1;
		}
		else if (organismStruct.nonspikingVector.size() != numNonSpikeSynapses) {
			std::cout << "Non-spiking synapse characteristic vector size and number of non-spiking synapses from config file mismatch! Resolve and try again." << std::endl;
			//error_handler(ERROR_NONSPIKING_VECTOR_SIZE_MISMATCH);
			return 1;
		}

		/**********************************************************************************************************************************************************\
		|***************************************************************	Electrical Synapses		***************************************************************|
		\**********************************************************************************************************************************************************/
		pugi::xml_object_range<pugi::xml_node_iterator> synapse_elec_list = Synapses.child("ElectricalSynapses").children();

		//	Generate electrical synapse counter for length of vector of structs
		unsigned int numElectricalSynapses = 0;
		
		//	Generate for loop to store neuronal electrical synapse in each organism
		for (synapse_elec_child = synapse_elec_list.begin(); synapse_elec_child != synapse_elec_list.end(); synapse_elec_child++) {
			// Load the electrical synapse values into the struct
			/*
			std::cout << "Name: "		<< synapse_elec_child->child("Name").child_value()		<< std::endl;
			std::cout << "\tID: "		<< synapse_elec_child->child("ID").child_value()			<< std::endl;
			std::cout << "\tType: "		<< synapse_elec_child->child("Type").child_value()		<< std::endl;
			std::cout << "\tLow Coup: "	<< synapse_elec_child->child("LowCoup").child_value()		<< std::endl;
			std::cout << "\tHi Coup: "	<< synapse_elec_child->child("HiCoup").child_value()		<< std::endl;
			std::cout << "\tTurn On V: "	<< synapse_elec_child->child("TurnOnV").child_value()		<< std::endl;
			std::cout << "\tSat. V: "	<< synapse_elec_child->child("SaturateV").child_value()	<< std::endl;
			*/
			electricalStruct.name		= (const std::string*)synapse_elec_child->child("Name").text().get();
			electricalStruct.id			= (const std::string*)synapse_elec_child->child("ID").text().get();
			electricalStruct.type		= (const std::string*)synapse_elec_child->child("Type").text().get();
			electricalStruct.lowcoup	= (const std::string*)synapse_elec_child->child("LowCoup").text().get();
			electricalStruct.hicoup		= (const std::string*)synapse_elec_child->child("HiCoup").text().get();
			electricalStruct.turnonv	= (const std::string*)synapse_elec_child->child("TurnOnV").text().get();
			electricalStruct.saturatev	= (const std::string*)synapse_elec_child->child("SaturateV").text().get();

			//	Make room for the new member struct by pushing the vector
			organismStruct.electricalVector.emplace_back(electricalStruct);

			// Increase electrical synapse counter
			numElectricalSynapses++;
		}
		std::cout << "total number of electrical synapses: " << numElectricalSynapses << std::endl;

		//	Check if the loaded vector is empty or has element
		if (organismStruct.electricalVector.empty()) {
			std::cout << "The electrical synapse vector loaded is empty." << std::endl;
			//error_handler(ERROR_ELECTRICAL_VECTOR_EMPTY);
			return 1;
		}
		else if (organismStruct.electricalVector.size() != numElectricalSynapses) {
			std::cout << "Electrical synapse characteristic vector size and number of electrical synapses from config file mismatch! Resolve and try again." << std::endl;
			//error_handler(ERROR_ELECTRICAL_VECTOR_SIZE_MISMATCH);
			return 1;
		}

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
			// Load the connexion values into the struct
			/*
			std::cout << "Name: "		<< connexion_child->child("Name").child_value()		<< std::endl;
			std::cout << "\tID: "		<< connexion_child->child("ID").child_value()			<< std::endl;
			std::cout << "\tType: "		<< connexion_child->child("Type").child_value()		<< std::endl;
			std::cout << "\tEquil: "		<< connexion_child->child("Equil").child_value()		<< std::endl;
			std::cout << "\tSynAmp: "	<< connexion_child->child("SynAmp").child_value()		<< std::endl;
			std::cout << "\tSat. V: "	<< connexion_child->child("SaturateV").child_value()	<< std::endl;
			*/
			
			connexionStruct.id				= (const std::string*)connexion_child->child("ID").text().get();
			connexionStruct.sourceid		= (const std::string*)connexion_child->child("SourceID").text().get();
			connexionStruct.targetid		= (const std::string*)connexion_child->child("TargetID").text().get();
			connexionStruct.type			= (const std::string*)connexion_child->child("Type").text().get();
			connexionStruct.synapsetypeid	= (const std::string*)connexion_child->child("SynapseTypeID").text().get();
			connexionStruct.delay			= (const std::string*)connexion_child->child("Delay").text().get();
			connexionStruct.g				= (const std::string*)connexion_child->child("G").text().get();
			
			//	Make room for the new member struct by pushing the vector
			organismStruct.connexionVector.emplace_back(connexionStruct);

			// Increase electrical synapse counter
			numConnexions++;
		}

		//	Check if the loaded vector is empty or has element
		if (organismStruct.connexionVector.empty()) {
			std::cout << "The connexion vector loaded is empty." << std::endl;
			//error_handler(ERROR_ELECTRICAL_VECTOR_EMPTY);
			return 1;
		}
		//	Test the size of the found loaded connexions
		if (organismStruct.connexionVector.size() != numConnexions){
			std::cout << "Connexion characteristic vector size and number of connexion from config file mismatch! Resolve and try again." << std::endl;
			//error_handler(ERROR_CONNEXION_VECTOR_SIZE_MISMATCH);
			return 1;
		}
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
	
		/**********************************************************************************************************************************************************\
		|
		|	Organism Section -
		|
		\**********************************************************************************************************************************************************/

		organismStruct.organism_id = (const std::string*)organism_parent.child("Organsim").child("ID").text().get();
		organismStruct.organism_name = (const std::string*)organism_parent.child("Organsim").child("Name").text().get();


		if ((const std::string*)organism_parent.child("Organsim").child("Name").text().get() != organismStruct.organism_name) {
			std::cout << "Error: found and stored names are not identical. Please fix and try again." << std::endl;
			std::cout << "\tFound organism name:\t" << (const std::string*)organism_parent.child("Organsim").child("Name").text().get() << std::endl;
			std::cout << "\tStored organism name:\t" << organismStruct.organism_name << std::endl;
		}

		//	Push back new organism created with default constructor
		organismVector.emplace_back(std::make_shared<Organisms>(organismStruct));
		numOrganisms++;
	}

	/**************************************************************************************\
	|		exit if user has time to read and validate stored data / printed data
	\**************************************************************************************/
	/*
	do {
		std::cout << "Press 'e' to exit: ";
		std::cin >> end;
		if (end == 'e' || end == 'E'){
			end = 1;
		}
	} while (end != 1);
	*/
	return 0;
};

/*************************************************************************************************************************************\
|
|		Get Configuration File Path -
|			Get the user to enter the path to the .asim model configuration file
|			Inputs:  None
|			Outputs: None
|				**This method will assign the loaded and validated file path to the neural model configuration
|				  file path to the configFilePath class member.
|
\*************************************************************************************************************************************/
void NeuralModel::get_config_file_path() {
	const char *	testPath;

	std::cout << "Enter the file path to the model configuration file (type: .asim): " << std::endl;
	std::cin >> configFilePath;

	testPath = &configFilePath[0];

	pugi::xml_document doc;
	pugi::xml_parse_result open_result = doc.load_file(testPath);

	if (open_result) {
		std::cout << open_result.description() << std::endl;
		return;
	}
	else {
		std::cout << "Error: " << open_result.description() << configFilePath << " empty. Please fix path and try again." << std::endl;
		//std::cout << "Error: File could not be opened. Check path entered and try again." << std::endl;
		//error_handler(ERROR_FILE_OPEN);
		return;
	}
};

/*************************************************************************************************************************************\
|
|		Print vector elements -
|			print a loaded vector element by element
|			expecting the input to be a vector of structs of vector of structs
|
|		NOTE: this will be moved into the class and call the class members from a method to print 1 method per class struct member
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

void NeuralModel::print_val(std::string tag, const std::string& value) {
	std::cout << tag << ": " << value << std::endl;
	return;
};