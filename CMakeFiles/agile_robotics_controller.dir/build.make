# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nvidia/dev/agile_robotics_contoller

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nvidia/dev/agile_robotics_contoller

# Include any dependencies generated for this target.
include CMakeFiles/agile_robotics_controller.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/agile_robotics_controller.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/agile_robotics_controller.dir/flags.make

CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o: CMakeFiles/agile_robotics_controller.dir/flags.make
CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o: code/include/device_control.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nvidia/dev/agile_robotics_contoller/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o -c /home/nvidia/dev/agile_robotics_contoller/code/include/device_control.cpp

CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nvidia/dev/agile_robotics_contoller/code/include/device_control.cpp > CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.i

CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nvidia/dev/agile_robotics_contoller/code/include/device_control.cpp -o CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.s

CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.requires:

.PHONY : CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.requires

CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.provides: CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.requires
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.provides.build
.PHONY : CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.provides

CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.provides.build: CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o


CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o: CMakeFiles/agile_robotics_controller.dir/flags.make
CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o: code/include/pugixml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nvidia/dev/agile_robotics_contoller/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o -c /home/nvidia/dev/agile_robotics_contoller/code/include/pugixml.cpp

CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nvidia/dev/agile_robotics_contoller/code/include/pugixml.cpp > CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.i

CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nvidia/dev/agile_robotics_contoller/code/include/pugixml.cpp -o CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.s

CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.requires:

.PHONY : CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.requires

CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.provides: CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.requires
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.provides.build
.PHONY : CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.provides

CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.provides.build: CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o


# Object files for target agile_robotics_controller
agile_robotics_controller_OBJECTS = \
"CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o" \
"CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o"

# External object files for target agile_robotics_controller
agile_robotics_controller_EXTERNAL_OBJECTS =

agile_robotics_controller: CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o
agile_robotics_controller: CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o
agile_robotics_controller: CMakeFiles/agile_robotics_controller.dir/build.make
agile_robotics_controller: CMakeFiles/agile_robotics_controller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nvidia/dev/agile_robotics_contoller/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable agile_robotics_controller"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/agile_robotics_controller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/agile_robotics_controller.dir/build: agile_robotics_controller

.PHONY : CMakeFiles/agile_robotics_controller.dir/build

CMakeFiles/agile_robotics_controller.dir/requires: CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o.requires
CMakeFiles/agile_robotics_controller.dir/requires: CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o.requires

.PHONY : CMakeFiles/agile_robotics_controller.dir/requires

CMakeFiles/agile_robotics_controller.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/agile_robotics_controller.dir/cmake_clean.cmake
.PHONY : CMakeFiles/agile_robotics_controller.dir/clean

CMakeFiles/agile_robotics_controller.dir/depend:
	cd /home/nvidia/dev/agile_robotics_contoller && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nvidia/dev/agile_robotics_contoller /home/nvidia/dev/agile_robotics_contoller /home/nvidia/dev/agile_robotics_contoller /home/nvidia/dev/agile_robotics_contoller /home/nvidia/dev/agile_robotics_contoller/CMakeFiles/agile_robotics_controller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/agile_robotics_controller.dir/depend
