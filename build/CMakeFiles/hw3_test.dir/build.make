# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/software/software/CMake/3.21.1-GCCcore-11.2.0/bin/cmake

# The command to remove a file.
RM = /opt/software/software/CMake/3.21.1-GCCcore-11.2.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/jjeilert/hw3/CIS_520_Project_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/jjeilert/hw3/CIS_520_Project_3/build

# Include any dependencies generated for this target.
include CMakeFiles/hw3_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hw3_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hw3_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw3_test.dir/flags.make

CMakeFiles/hw3_test.dir/test/tests.cpp.o: CMakeFiles/hw3_test.dir/flags.make
CMakeFiles/hw3_test.dir/test/tests.cpp.o: ../test/tests.cpp
CMakeFiles/hw3_test.dir/test/tests.cpp.o: CMakeFiles/hw3_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/jjeilert/hw3/CIS_520_Project_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw3_test.dir/test/tests.cpp.o"
	/opt/software/software/GCCcore/11.2.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw3_test.dir/test/tests.cpp.o -MF CMakeFiles/hw3_test.dir/test/tests.cpp.o.d -o CMakeFiles/hw3_test.dir/test/tests.cpp.o -c /homes/jjeilert/hw3/CIS_520_Project_3/test/tests.cpp

CMakeFiles/hw3_test.dir/test/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3_test.dir/test/tests.cpp.i"
	/opt/software/software/GCCcore/11.2.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /homes/jjeilert/hw3/CIS_520_Project_3/test/tests.cpp > CMakeFiles/hw3_test.dir/test/tests.cpp.i

CMakeFiles/hw3_test.dir/test/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3_test.dir/test/tests.cpp.s"
	/opt/software/software/GCCcore/11.2.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /homes/jjeilert/hw3/CIS_520_Project_3/test/tests.cpp -o CMakeFiles/hw3_test.dir/test/tests.cpp.s

# Object files for target hw3_test
hw3_test_OBJECTS = \
"CMakeFiles/hw3_test.dir/test/tests.cpp.o"

# External object files for target hw3_test
hw3_test_EXTERNAL_OBJECTS =

hw3_test: CMakeFiles/hw3_test.dir/test/tests.cpp.o
hw3_test: CMakeFiles/hw3_test.dir/build.make
hw3_test: libblock_store.a
hw3_test: CMakeFiles/hw3_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/jjeilert/hw3/CIS_520_Project_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw3_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw3_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw3_test.dir/build: hw3_test
.PHONY : CMakeFiles/hw3_test.dir/build

CMakeFiles/hw3_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw3_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw3_test.dir/clean

CMakeFiles/hw3_test.dir/depend:
	cd /homes/jjeilert/hw3/CIS_520_Project_3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/jjeilert/hw3/CIS_520_Project_3 /homes/jjeilert/hw3/CIS_520_Project_3 /homes/jjeilert/hw3/CIS_520_Project_3/build /homes/jjeilert/hw3/CIS_520_Project_3/build /homes/jjeilert/hw3/CIS_520_Project_3/build/CMakeFiles/hw3_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw3_test.dir/depend

