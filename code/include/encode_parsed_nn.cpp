//	Standard libraries
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>
//	Non-Standard libraries
//#inculde "error_handler.h

//	Custom made header files
#include "model_config_data.hpp"
#include "system_defines.hpp"

int main(int argc, char** argv ){
	/*	Creating the vector for the class and allocate the room for the vector.	*/
	std::shared_ptr<NeuralModel> neural_model_main = std::make_shared<NeuralModel>();

	neural_model_main->parse_config_file();

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
	std::system("PAUSE");
	//std::cin.get();

	return 0;
}