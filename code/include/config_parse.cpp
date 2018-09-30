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
	Neurons				neuronStruct;
	Connexions			connexionStruct;
	SynapsesSpiking		spikingStruct;
	SynapsesElectrical  electricalStruct;
	SynapsesNonSpiking	nonspikingStruct;
	Organisms		    organismStruct;
	
	// Instantiate and generate the organism vector struct
	//std::vector<std::shared_ptr<Organisms>>	organismVector;
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
			neuronStruct.name						= (std::string)neuron_child->child("Name").text().get();
			neuronStruct.id							= (std::string)neuron_child->child("ID").text().get();
			neuronStruct.enabled					= (std::string)neuron_child->child("Enabled").text().get();
			neuronStruct.tonicstimulus				= (std::string)neuron_child->child("TonicStimulus").text().get();
			neuronStruct.noise						= (std::string)neuron_child->child("Noise").text().get();
			neuronStruct.restingpot					= (std::string)neuron_child->child("RestingPot").text().get();
			neuronStruct.size						= (std::string)neuron_child->child("Size").text().get();
			neuronStruct.timeconst					= (std::string)neuron_child->child("TimeConst").text().get();
			neuronStruct.initthresh					= (std::string)neuron_child->child("InitialThresh").text().get();
			neuronStruct.relativeaccom				= (std::string)neuron_child->child("RelativeAccom").text().get();
			neuronStruct.accomtimeconst				= (std::string)neuron_child->child("AccomTimeConst").text().get();
			neuronStruct.ahpamp						= (std::string)neuron_child->child("AHPAmp").text().get();
			neuronStruct.ahptimeconst				= (std::string)neuron_child->child("AHPTimeConst").text().get();
			neuronStruct.gmaxca						= (std::string)neuron_child->child("GMaxCa").text().get();
			neuronStruct.burstinitatbottom			= (std::string)neuron_child->child("BurstInitAtBottom").text().get();
			neuronStruct.caactive_id				= (std::string)neuron_child->child("CaActivation").child("ID").text().get();
			neuronStruct.caactive_midpoint			= (std::string)neuron_child->child("CaActivation").child("MidPoint").text().get();
			neuronStruct.caactive_slope				= (std::string)neuron_child->child("CaActivation").child("Slope").text().get();
			neuronStruct.caactive_timeconst			= (std::string)neuron_child->child("CaActivation").child("TimeConstant").text().get();
			neuronStruct.caactive_activatetype		= (std::string)neuron_child->child("CaActivation").child("ActivationType").text().get();
			neuronStruct.cadeactive_id				= (std::string)neuron_child->child("CaDeactivation").child("ID").text().get();
			neuronStruct.cadeactive_midpoint		= (std::string)neuron_child->child("CaDeactivation").child("MidPoint").text().get();
			neuronStruct.cadeactive_slope			= (std::string)neuron_child->child("CaDeactivation").child("Slope").text().get();
			neuronStruct.cadeactive_timeconst		= (std::string)neuron_child->child("CaDeactivation").child("TimeConstant").text().get();
			neuronStruct.cadeactive_activatetype	= (std::string)neuron_child->child("CaDeactivation").child("ActivationType").text().get();
	
			//	Make room for the new member struct by pushing the vector
			//organismStruct.neuronVector.emplace_back(std::make_shared<Neurons>(neuronStruct));
			organismStruct.neuronVector.emplace_back(neuronStruct);
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
		
	/*
		//	Print the found elements
		for (int i = 0, size = organismStruct.neuronVector.size(); i < size; ++i) {
			std::cout << "organism name:\t" << &organismStruct.neuronVector[i] << std::endl;
		}
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

		//	generate for loop to store neuronal spiking synapse in each organism
		for (synapse_spiking_child = synapse_spiking_list.begin(); synapse_spiking_child != synapse_spiking_list.end(); synapse_spiking_child++) {
			// Load the spiking synapse values into a struct
			spikingStruct.name			= (std::string)synapse_spiking_child->child("Name").text().get();
			spikingStruct.id			= (std::string)synapse_spiking_child->child("ID").text().get();
			spikingStruct.type			= (std::string)synapse_spiking_child->child("Type").text().get();
			spikingStruct.equil			= (std::string)synapse_spiking_child->child("Equil").text().get();
			spikingStruct.synamp		= (std::string)synapse_spiking_child->child("SynAmp").text().get();
			spikingStruct.decay			= (std::string)synapse_spiking_child->child("Decay").text().get();
			spikingStruct.relfacil		= (std::string)synapse_spiking_child->child("RelFacil").text().get();
			spikingStruct.facildecay	= (std::string)synapse_spiking_child->child("FacilDecay").text().get();
			spikingStruct.voltdep		= (std::string)synapse_spiking_child->child("VoltDep").text().get();
			spikingStruct.maxrelcond	= (std::string)synapse_spiking_child->child("MaxRelCond").text().get();
			spikingStruct.satpspot		= (std::string)synapse_spiking_child->child("SatPSPot").text().get();
			spikingStruct.threshpspot	= (std::string)synapse_spiking_child->child("ThreshPSPot").text().get();
			spikingStruct.hebbian		= (std::string)synapse_spiking_child->child("Hebbian").text().get();
			spikingStruct.maxaugcond	= (std::string)synapse_spiking_child->child("MaxAugCond").text().get();
			spikingStruct.learninginc	= (std::string)synapse_spiking_child->child("LearningInc").text().get();
			spikingStruct.learningtime	= (std::string)synapse_spiking_child->child("LearningTime").text().get();
			spikingStruct.allowforget	= (std::string)synapse_spiking_child->child("AllowForget").text().get();
			spikingStruct.forgettime	= (std::string)synapse_spiking_child->child("ForgetTime").text().get();
			spikingStruct.consolidation	= (std::string)synapse_spiking_child->child("Consolidation").text().get();
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
			nonspikingStruct.name		= (std::string)synapse_nonspiking_child->child("Name").text().get();
			nonspikingStruct.id			= (std::string)synapse_nonspiking_child->child("ID").text().get();
			nonspikingStruct.type		= (std::string)synapse_nonspiking_child->child("Type").text().get();
			nonspikingStruct.equil		= (std::string)synapse_nonspiking_child->child("Equil").text().get();
			nonspikingStruct.synamp		= (std::string)synapse_nonspiking_child->child("SynAmp").text().get();
			nonspikingStruct.saturatev	= (std::string)synapse_nonspiking_child->child("SaturateV").text().get();

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
			electricalStruct.name		= (std::string)synapse_elec_child->child("Name").text().get();
			electricalStruct.id			= (std::string)synapse_elec_child->child("ID").text().get();
			electricalStruct.type		= (std::string)synapse_elec_child->child("Type").text().get();
			electricalStruct.lowcoup	= (std::string)synapse_elec_child->child("LowCoup").text().get();
			electricalStruct.hicoup		= (std::string)synapse_elec_child->child("HiCoup").text().get();
			electricalStruct.turnonv	= (std::string)synapse_elec_child->child("TurnOnV").text().get();
			electricalStruct.saturatev	= (std::string)synapse_elec_child->child("SaturateV").text().get();

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
			connexionStruct.id				= (std::string)connexion_child->child("ID").text().get();
			connexionStruct.sourceid		= (std::string)connexion_child->child("SourceID").text().get();
			connexionStruct.targetid		= (std::string)connexion_child->child("TargetID").text().get();
			connexionStruct.type			= (std::string)connexion_child->child("Type").text().get();
			connexionStruct.synapsetypeid	= (std::string)connexion_child->child("SynapseTypeID").text().get();
			connexionStruct.delay			= (std::string)connexion_child->child("Delay").text().get();
			connexionStruct.g				= (std::string)connexion_child->child("G").text().get();
			
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

		organismStruct.organism_id = (std::string)organism_parent.child("Organsim").child("ID").text().get();
		organismStruct.organism_name = (std::string)organism_parent.child("Organsim").child("Name").text().get();


		if ((std::string)organism_parent.child("Organsim").child("Name").text().get() != organismStruct.organism_name) {
			std::cout << "Error: found and stored names are not identical. Please fix and try again." << std::endl;
			std::cout << "\tFound organism name:\t" << (std::string)organism_parent.child("Organsim").child("Name").text().get() << std::endl;
			std::cout << "\tStored organism name:\t" << organismStruct.organism_name << std::endl;
		}

		//	Push back new organism created with default constructor
		//organismVector.emplace_back(std::make_shared<Organisms>(organismStruct));
		organismVector.emplace_back(organismStruct);
	
		for (int i = 0, size = organismStruct.neuronVector.size(); i < size; i++) {
			Neurons* pntr = &organismVector[numOrganisms].neuronVector[i];
			std::cout << "Neuron ID: " << pntr->id << std::endl;
		}
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
	const char *testPath;

	std::cout << "Enter the file path to the model configuration file (type: .xml): " << std::endl;
	std::cin >> configFilePath;

	testPath = &configFilePath[0];

	pugi::xml_document doc;
	pugi::xml_parse_result open_result = doc.load_file(testPath);

	if (open_result) {
		std::cout << open_result.description() << std::endl;
		return;
	}
	else {
		std::cout << "Error: " << open_result.description() << " " 
				  << configFilePath << " empty. Please fix path and try again." << std::endl;
		//error_handler(ERROR_FILE_OPEN);
		std::system("PAUSE");
		exit(1);
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

void NeuralModel::transferOrganism() {
	for (int i = 0, size = organismVector.size(); i < size; i++) {
		// Generate a pointer to the organism we will be generating in the device
		Organisms *org_ptr = &organismVector[i];

		// Organism specific data aquisition and transfer
		std::string temp_org_id		= org_ptr->organism_id;
		std::string temp_org_name	= org_ptr->organism_name;
		std::string temp_nm_id		= org_ptr->neuralmodule_id;
		std::string temp_nm_name	= org_ptr->neuralmodule_name;
		
		// Get the Neuron data
		transferNeurons(org_ptr);

		// Get the Non-Synapse data ***Expanding to use all synapse types later
		transferNonSpikingSynapses(org_ptr);

		// Get the Connexion data
		transferConnexions(org_ptr);
	}
	std::cout << "Completed transfering data to device." << std::endl;
}

void NeuralModel::transferNeurons(Organisms *org_ptr) {

	/*
	int memsize = sizeof(org_ptr->neuronVector);

	std::vector<NeuralModel::Neurons> *neuronvect = org_ptr->neuronVector;

	cudaMemAlloc(neuronvect, org->neuronVect, memsize, cudaMemHostToDevice);

	*/

	for (int j = 0, size = org_ptr->neuronVector.size(); j < size; j++) {
		// this should be altered to be cudaMemAlloc where we allocate the gpu cache memory for the model
		std::string temp_id					= org_ptr->neuronVector[j].id;
		std::string temp_name				= org_ptr->neuronVector[j].name;
		std::string temp_enabled			= org_ptr->neuronVector[j].enabled;
		std::string temp_tonicstimulus		= org_ptr->neuronVector[j].tonicstimulus;
		std::string temp_noise				= org_ptr->neuronVector[j].noise;
		std::string temp_restingpot			= org_ptr->neuronVector[j].restingpot;
		std::string temp_size				= org_ptr->neuronVector[j].size;
		std::string temp_timeconst			= org_ptr->neuronVector[j].timeconst;
		std::string temp_initthresh			= org_ptr->neuronVector[j].initthresh;
		std::string temp_relativeaccom		= org_ptr->neuronVector[j].relativeaccom;
		std::string temp_accomtimeconst		= org_ptr->neuronVector[j].accomtimeconst;
		std::string temp_ahpamp				= org_ptr->neuronVector[j].ahpamp;
		std::string temp_ahptimeconst		= org_ptr->neuronVector[j].ahptimeconst;
		std::string temp_gmaxca				= org_ptr->neuronVector[j].gmaxca;
		std::string temp_burstinitatbottom	= org_ptr->neuronVector[j].burstinitatbottom;
		std::string temp_caatice_id					= org_ptr->neuronVector[j].caactive_id;
		std::string temp_caactive_midpoint			= org_ptr->neuronVector[j].caactive_midpoint;
		std::string temp_caactive_slope				= org_ptr->neuronVector[j].caactive_slope;
		std::string temp_caactive_timeconst			= org_ptr->neuronVector[j].caactive_timeconst;
		std::string temp_caactive_activatetype		= org_ptr->neuronVector[j].caactive_activatetype;
		std::string temp_cadeactive_id				= org_ptr->neuronVector[j].cadeactive_id;
		std::string temp_cadeactive_midpoint		= org_ptr->neuronVector[j].cadeactive_midpoint;
		std::string temp_cadeactive_slope			= org_ptr->neuronVector[j].cadeactive_slope;
		std::string temp_cadeactive_timeconst		= org_ptr->neuronVector[j].cadeactive_timeconst;
		std::string temp_cadeactive_activatetype	= org_ptr->neuronVector[j].cadeactive_activatetype;
		std::cout << "Neuron ID: " << temp_id << std::endl;
	}
}

void NeuralModel::transferNonSpikingSynapses(Organisms *org_ptr) {
	for (int j = 0, size = org_ptr->nonspikingVector.size(); j < size; j++) {
		// this should be altered to be cudaMemAlloc where we allocate the gpu cache memory for the model
		std::string temp_id			= org_ptr->nonspikingVector[j].id;
		std::string temp_name		= org_ptr->nonspikingVector[j].name;
		std::string temp_type		= org_ptr->nonspikingVector[j].type;
		std::string temp_equil		= org_ptr->nonspikingVector[j].equil;
		std::string temp_synamp		= org_ptr->nonspikingVector[j].synamp;
		std::string temp_saturatev	= org_ptr->nonspikingVector[j].saturatev;
		std::cout << "Non-Spiking Synapse ID: " << temp_id << std::endl;
	}
}

void NeuralModel::transferConnexions(Organisms *org_ptr) {
	for (int j = 0, size = org_ptr->connexionVector.size(); j < size; j++) {
		// this should be altered to be cudaMemAlloc where we allocate the gpu cache memory for the model
		std::string temp_id				= org_ptr->connexionVector[j].id;
		std::string temp_sourceid		= org_ptr->connexionVector[j].sourceid;
		std::string temp_targetid		= org_ptr->connexionVector[j].targetid;
		std::string temp_type			= org_ptr->connexionVector[j].type;
		std::string temp_synapsetypeid	= org_ptr->connexionVector[j].synapsetypeid;
		std::string temp_delay			= org_ptr->connexionVector[j].delay;
		std::string temp_g				= org_ptr->connexionVector[j].g;
		std::cout << "Connixion ID:\t" << temp_id << "\n\tsource:\t" << temp_sourceid << "\n\ttarget:\t" << temp_targetid << std::endl;
	}
}
