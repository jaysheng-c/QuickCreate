# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /apps/yoshino/bin/cmake

# The command to remove a file.
RM = /apps/yoshino/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/workspace/QuickCreate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/QuickCreate/build

# Include any dependencies generated for this target.
include CMakeFiles/QuickCreate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/QuickCreate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QuickCreate.dir/flags.make

CMakeFiles/QuickCreate.dir/test/main.cpp.o: CMakeFiles/QuickCreate.dir/flags.make
CMakeFiles/QuickCreate.dir/test/main.cpp.o: ../test/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/QuickCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QuickCreate.dir/test/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QuickCreate.dir/test/main.cpp.o -c /root/workspace/QuickCreate/test/main.cpp

CMakeFiles/QuickCreate.dir/test/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QuickCreate.dir/test/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/QuickCreate/test/main.cpp > CMakeFiles/QuickCreate.dir/test/main.cpp.i

CMakeFiles/QuickCreate.dir/test/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QuickCreate.dir/test/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/QuickCreate/test/main.cpp -o CMakeFiles/QuickCreate.dir/test/main.cpp.s

# Object files for target QuickCreate
QuickCreate_OBJECTS = \
"CMakeFiles/QuickCreate.dir/test/main.cpp.o"

# External object files for target QuickCreate
QuickCreate_EXTERNAL_OBJECTS =

../bin/QuickCreate: CMakeFiles/QuickCreate.dir/test/main.cpp.o
../bin/QuickCreate: CMakeFiles/QuickCreate.dir/build.make
../bin/QuickCreate: CMakeFiles/QuickCreate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/QuickCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/QuickCreate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QuickCreate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QuickCreate.dir/build: ../bin/QuickCreate

.PHONY : CMakeFiles/QuickCreate.dir/build

CMakeFiles/QuickCreate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QuickCreate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QuickCreate.dir/clean

CMakeFiles/QuickCreate.dir/depend:
	cd /root/workspace/QuickCreate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/QuickCreate /root/workspace/QuickCreate /root/workspace/QuickCreate/build /root/workspace/QuickCreate/build /root/workspace/QuickCreate/build/CMakeFiles/QuickCreate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QuickCreate.dir/depend
