//	Standard libraries
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <iostream>

//	Non-Standard libraries
#include "pugixml.hpp"

//	Custom made header files
#include "config_data.hpp"
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

	std::cin.get();

	return 0;
};