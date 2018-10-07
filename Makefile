# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nvidia/dev/agile_robotics_contoller/CMakeFiles /home/nvidia/dev/agile_robotics_contoller/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nvidia/dev/agile_robotics_contoller/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named agile_robotics_controller

# Build rule for target.
agile_robotics_controller: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 agile_robotics_controller
.PHONY : agile_robotics_controller

# fast build rule for target.
agile_robotics_controller/fast:
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/build
.PHONY : agile_robotics_controller/fast

code/include/device_control.o: code/include/device_control.cpp.o

.PHONY : code/include/device_control.o

# target to build an object file
code/include/device_control.cpp.o:
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.o
.PHONY : code/include/device_control.cpp.o

code/include/device_control.i: code/include/device_control.cpp.i

.PHONY : code/include/device_control.i

# target to preprocess a source file
code/include/device_control.cpp.i:
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.i
.PHONY : code/include/device_control.cpp.i

code/include/device_control.s: code/include/device_control.cpp.s

.PHONY : code/include/device_control.s

# target to generate assembly for a file
code/include/device_control.cpp.s:
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/device_control.cpp.s
.PHONY : code/include/device_control.cpp.s

code/include/pugixml.o: code/include/pugixml.cpp.o

.PHONY : code/include/pugixml.o

# target to build an object file
code/include/pugixml.cpp.o:
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.o
.PHONY : code/include/pugixml.cpp.o

code/include/pugixml.i: code/include/pugixml.cpp.i

.PHONY : code/include/pugixml.i

# target to preprocess a source file
code/include/pugixml.cpp.i:
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.i
.PHONY : code/include/pugixml.cpp.i

code/include/pugixml.s: code/include/pugixml.cpp.s

.PHONY : code/include/pugixml.s

# target to generate assembly for a file
code/include/pugixml.cpp.s:
	$(MAKE) -f CMakeFiles/agile_robotics_controller.dir/build.make CMakeFiles/agile_robotics_controller.dir/code/include/pugixml.cpp.s
.PHONY : code/include/pugixml.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... agile_robotics_controller"
	@echo "... code/include/device_control.o"
	@echo "... code/include/device_control.i"
	@echo "... code/include/device_control.s"
	@echo "... code/include/pugixml.o"
	@echo "... code/include/pugixml.i"
	@echo "... code/include/pugixml.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
