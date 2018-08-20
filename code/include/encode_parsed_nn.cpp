//	Standard libraries
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>
//	Non-Standard libraries
//#inculde "error_handler.h
#include "model_config_data.hpp"
#include "system_defines.hpp"

int main(int argc, char** argv ){
	std::string get_config_file;
	NeuralModel* neuralmodel;

	std::cout << "Enter model file path (.asim type): ";
	std::cin >> get_config_file; 

    neuralmodel->configFilePath = get_config_file;

    neuralmodel->parse_model_config();

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
	std::cin.get();
	return 0;
}