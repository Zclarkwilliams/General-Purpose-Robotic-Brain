cmake_minimum_required (VERSION 3.5)
# Project name
project (agile_robotics_controller)

# Count the processors used
include(ProcessorCount)

ProcessorCount(N)
message("Number of processors: ${N}")
message("Initializing File List CMakeLists.txt")

# Project version
set(agile_robotics_controller_VERSION_MAJOR 0)
set(agile_robotics_controller_VERSION_MINOR 1)

# Enable all the flags and set the c++ standard
set (CMAKE_CXX_FLAGS "${CMAK_CXX_FLAGS} -Wall -Werror -std=c++17")

# Set up the path to the project directory
set (PROJ_DIR "${PROJECT_SOURCE_DIR}")
message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${PROJ_DIR}")
set(LIBRARY_OUTPUT_PATH "${PROJ_DIR}")

# Set up the path to source main.cpp
set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/code/src")
file (GLOB source_files "${SOURCE_DIR}/.cpp")
include_directories(agile_robotics_controller "${source_files}")
#add_executable (agile_robotics_controller "${source_files}")

# Set up the path to include files and libraries
set (includes_dir "${PROJECT_SOURCE_DIR}/code/include")
file (GLOB include_files "${includes_dir}/.hpp")
include_directories(agile_robotics_controller "${include_files}")

# Add pugixml library to teh project
#add_library(pugixml pugixml.cpp)

# Link the "include" file directory
#include_directories (agile_robotics_controller "${include_files}")
#add_subdirectory (pugixml)
#target_link_libraries(agile_robotics_controller pugixml)
