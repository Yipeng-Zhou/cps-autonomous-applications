# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/cps-student-2/cps-lab-workspace/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cps-student-2/cps-lab-workspace/build

# Utility rule file for exercise3_geneus.

# Include the progress variables for this target.
include exercise3/CMakeFiles/exercise3_geneus.dir/progress.make

exercise3_geneus: exercise3/CMakeFiles/exercise3_geneus.dir/build.make

.PHONY : exercise3_geneus

# Rule to build all files generated by this target.
exercise3/CMakeFiles/exercise3_geneus.dir/build: exercise3_geneus

.PHONY : exercise3/CMakeFiles/exercise3_geneus.dir/build

exercise3/CMakeFiles/exercise3_geneus.dir/clean:
	cd /home/cps-student-2/cps-lab-workspace/build/exercise3 && $(CMAKE_COMMAND) -P CMakeFiles/exercise3_geneus.dir/cmake_clean.cmake
.PHONY : exercise3/CMakeFiles/exercise3_geneus.dir/clean

exercise3/CMakeFiles/exercise3_geneus.dir/depend:
	cd /home/cps-student-2/cps-lab-workspace/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cps-student-2/cps-lab-workspace/src /home/cps-student-2/cps-lab-workspace/src/exercise3 /home/cps-student-2/cps-lab-workspace/build /home/cps-student-2/cps-lab-workspace/build/exercise3 /home/cps-student-2/cps-lab-workspace/build/exercise3/CMakeFiles/exercise3_geneus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : exercise3/CMakeFiles/exercise3_geneus.dir/depend

