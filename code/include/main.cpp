//	Standard libraries
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <iostream>

//	Non-Standard libraries
//#inculde "error_handler.h
#include "pugixml.hpp"


//	Custom made header files
#include "model_config_data.hpp"
#include "system_defines.hpp"
#include "device_control.cpp"

void generate_model(std::shared_ptr<SimulationModel> simmodel_ptr) {
	// Transfer model configuration into the GPU cache
	simmodel_ptr->transferOrganism();
};


int main(int argc, char** argv){
	/*	Creating the vector for the class and allocate the room for the vector.	*/
	std::shared_ptr<SimulationModel> SimulationModelMain = std::make_shared<SimulationModel>();
	
	// Is file valid to open
/*	if (argc != 2) {
		std::cout << "\nPlease include 1 argument that is the file path to the neural model configuration (.asim). \n\n" << std::endl;
		std::system("PAUSE");
		return 1;
	}
*/
	int comp;
	comp = SimulationModelMain->parse_config_file();
	if (comp != 0) {
		// Exit on this error
		return 1;
	}
	generate_model(SimulationModelMain);

	/*
    Organisms organism;

    for (int i = 0, size = organism[0].neuron.size(); i < size; ++i){
		cout << "Name:\t\t"		    << organism[0].synapse_nonspiking[i].name       << endl;
		cout << "\tID: \t\t"		<< organism[0].synapse_nonspiking[i].id		    << endl;
		cout << "\tType: \t\t"		<< organism[0].synapse_nonspiking[i].type		<< endl;
		cout << "\tEquil: \t\t"		<< organism[0].synapse_nonspiking[i].equil		<< endl;
		cout << "\tSynAmp: \t\t"	<< organism[0].synapse_nonspiking[i].synamp	    << endl;
		cout << "\tSat. V: \t\t"	<< organism[0].synapse_nonspiking[i].saturatev	<< endl;
		cout << "	" << endl;
	};
	*/

	//std::system("PAUSE");
	std::cin.get();

	return 0;
};