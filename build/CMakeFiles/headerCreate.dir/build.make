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
include CMakeFiles/headerCreate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/headerCreate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/headerCreate.dir/flags.make

CMakeFiles/headerCreate.dir/test/test_header_create.cpp.o: CMakeFiles/headerCreate.dir/flags.make
CMakeFiles/headerCreate.dir/test/test_header_create.cpp.o: ../test/test_header_create.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/QuickCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/headerCreate.dir/test/test_header_create.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/headerCreate.dir/test/test_header_create.cpp.o -c /root/workspace/QuickCreate/test/test_header_create.cpp

CMakeFiles/headerCreate.dir/test/test_header_create.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/headerCreate.dir/test/test_header_create.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/QuickCreate/test/test_header_create.cpp > CMakeFiles/headerCreate.dir/test/test_header_create.cpp.i

CMakeFiles/headerCreate.dir/test/test_header_create.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/headerCreate.dir/test/test_header_create.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/QuickCreate/test/test_header_create.cpp -o CMakeFiles/headerCreate.dir/test/test_header_create.cpp.s

CMakeFiles/headerCreate.dir/src/CommandParser.cpp.o: CMakeFiles/headerCreate.dir/flags.make
CMakeFiles/headerCreate.dir/src/CommandParser.cpp.o: ../src/CommandParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/QuickCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/headerCreate.dir/src/CommandParser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/headerCreate.dir/src/CommandParser.cpp.o -c /root/workspace/QuickCreate/src/CommandParser.cpp

CMakeFiles/headerCreate.dir/src/CommandParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/headerCreate.dir/src/CommandParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/QuickCreate/src/CommandParser.cpp > CMakeFiles/headerCreate.dir/src/CommandParser.cpp.i

CMakeFiles/headerCreate.dir/src/CommandParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/headerCreate.dir/src/CommandParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/QuickCreate/src/CommandParser.cpp -o CMakeFiles/headerCreate.dir/src/CommandParser.cpp.s

# Object files for target headerCreate
headerCreate_OBJECTS = \
"CMakeFiles/headerCreate.dir/test/test_header_create.cpp.o" \
"CMakeFiles/headerCreate.dir/src/CommandParser.cpp.o"

# External object files for target headerCreate
headerCreate_EXTERNAL_OBJECTS =

../bin/headerCreate: CMakeFiles/headerCreate.dir/test/test_header_create.cpp.o
../bin/headerCreate: CMakeFiles/headerCreate.dir/src/CommandParser.cpp.o
../bin/headerCreate: CMakeFiles/headerCreate.dir/build.make
../bin/headerCreate: CMakeFiles/headerCreate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/QuickCreate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/headerCreate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/headerCreate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/headerCreate.dir/build: ../bin/headerCreate

.PHONY : CMakeFiles/headerCreate.dir/build

CMakeFiles/headerCreate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/headerCreate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/headerCreate.dir/clean

CMakeFiles/headerCreate.dir/depend:
	cd /root/workspace/QuickCreate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/QuickCreate /root/workspace/QuickCreate /root/workspace/QuickCreate/build /root/workspace/QuickCreate/build /root/workspace/QuickCreate/build/CMakeFiles/headerCreate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/headerCreate.dir/depend

