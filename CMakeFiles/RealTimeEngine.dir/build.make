# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/philar-8/s0017d-1-linux-scripting-Nechrito

# Include any dependencies generated for this target.
include CMakeFiles/RealTimeEngine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RealTimeEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RealTimeEngine.dir/flags.make

CMakeFiles/RealTimeEngine.dir/code/Application.o: CMakeFiles/RealTimeEngine.dir/flags.make
CMakeFiles/RealTimeEngine.dir/code/Application.o: projects/RealTimeEngine/code/Application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RealTimeEngine.dir/code/Application.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RealTimeEngine.dir/code/Application.o -c /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Application.cpp

CMakeFiles/RealTimeEngine.dir/code/Application.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealTimeEngine.dir/code/Application.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Application.cpp > CMakeFiles/RealTimeEngine.dir/code/Application.i

CMakeFiles/RealTimeEngine.dir/code/Application.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealTimeEngine.dir/code/Application.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Application.cpp -o CMakeFiles/RealTimeEngine.dir/code/Application.s

CMakeFiles/RealTimeEngine.dir/code/Camera.o: CMakeFiles/RealTimeEngine.dir/flags.make
CMakeFiles/RealTimeEngine.dir/code/Camera.o: projects/RealTimeEngine/code/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RealTimeEngine.dir/code/Camera.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RealTimeEngine.dir/code/Camera.o -c /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Camera.cpp

CMakeFiles/RealTimeEngine.dir/code/Camera.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealTimeEngine.dir/code/Camera.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Camera.cpp > CMakeFiles/RealTimeEngine.dir/code/Camera.i

CMakeFiles/RealTimeEngine.dir/code/Camera.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealTimeEngine.dir/code/Camera.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Camera.cpp -o CMakeFiles/RealTimeEngine.dir/code/Camera.s

CMakeFiles/RealTimeEngine.dir/code/LightNode.o: CMakeFiles/RealTimeEngine.dir/flags.make
CMakeFiles/RealTimeEngine.dir/code/LightNode.o: projects/RealTimeEngine/code/LightNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RealTimeEngine.dir/code/LightNode.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RealTimeEngine.dir/code/LightNode.o -c /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/LightNode.cpp

CMakeFiles/RealTimeEngine.dir/code/LightNode.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealTimeEngine.dir/code/LightNode.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/LightNode.cpp > CMakeFiles/RealTimeEngine.dir/code/LightNode.i

CMakeFiles/RealTimeEngine.dir/code/LightNode.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealTimeEngine.dir/code/LightNode.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/LightNode.cpp -o CMakeFiles/RealTimeEngine.dir/code/LightNode.s

CMakeFiles/RealTimeEngine.dir/code/Model.o: CMakeFiles/RealTimeEngine.dir/flags.make
CMakeFiles/RealTimeEngine.dir/code/Model.o: projects/RealTimeEngine/code/Model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/RealTimeEngine.dir/code/Model.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RealTimeEngine.dir/code/Model.o -c /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Model.cpp

CMakeFiles/RealTimeEngine.dir/code/Model.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealTimeEngine.dir/code/Model.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Model.cpp > CMakeFiles/RealTimeEngine.dir/code/Model.i

CMakeFiles/RealTimeEngine.dir/code/Model.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealTimeEngine.dir/code/Model.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Model.cpp -o CMakeFiles/RealTimeEngine.dir/code/Model.s

CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.o: CMakeFiles/RealTimeEngine.dir/flags.make
CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.o: projects/RealTimeEngine/code/RealTimeEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.o -c /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/RealTimeEngine.cpp

CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/RealTimeEngine.cpp > CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.i

CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/RealTimeEngine.cpp -o CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.s

CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.o: CMakeFiles/RealTimeEngine.dir/flags.make
CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.o: projects/RealTimeEngine/code/SoftwareRenderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.o -c /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/SoftwareRenderer.cpp

CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/SoftwareRenderer.cpp > CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.i

CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/SoftwareRenderer.cpp -o CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.s

CMakeFiles/RealTimeEngine.dir/code/Transform.o: CMakeFiles/RealTimeEngine.dir/flags.make
CMakeFiles/RealTimeEngine.dir/code/Transform.o: projects/RealTimeEngine/code/Transform.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/RealTimeEngine.dir/code/Transform.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RealTimeEngine.dir/code/Transform.o -c /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Transform.cpp

CMakeFiles/RealTimeEngine.dir/code/Transform.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RealTimeEngine.dir/code/Transform.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Transform.cpp > CMakeFiles/RealTimeEngine.dir/code/Transform.i

CMakeFiles/RealTimeEngine.dir/code/Transform.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RealTimeEngine.dir/code/Transform.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/code/Transform.cpp -o CMakeFiles/RealTimeEngine.dir/code/Transform.s

# Object files for target RealTimeEngine
RealTimeEngine_OBJECTS = \
"CMakeFiles/RealTimeEngine.dir/code/Application.o" \
"CMakeFiles/RealTimeEngine.dir/code/Camera.o" \
"CMakeFiles/RealTimeEngine.dir/code/LightNode.o" \
"CMakeFiles/RealTimeEngine.dir/code/Model.o" \
"CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.o" \
"CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.o" \
"CMakeFiles/RealTimeEngine.dir/code/Transform.o"

# External object files for target RealTimeEngine
RealTimeEngine_EXTERNAL_OBJECTS =

RealTimeEngine: CMakeFiles/RealTimeEngine.dir/code/Application.o
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/code/Camera.o
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/code/LightNode.o
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/code/Model.o
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.o
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.o
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/code/Transform.o
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/build.make
RealTimeEngine: CMakeFiles/RealTimeEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable RealTimeEngine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RealTimeEngine.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy_directory /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/models/ /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine/bin/models/

# Rule to build all files generated by this target.
CMakeFiles/RealTimeEngine.dir/build: RealTimeEngine

.PHONY : CMakeFiles/RealTimeEngine.dir/build

CMakeFiles/RealTimeEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RealTimeEngine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RealTimeEngine.dir/clean

CMakeFiles/RealTimeEngine.dir/depend:
	cd /home/philar-8/s0017d-1-linux-scripting-Nechrito && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine /home/philar-8/s0017d-1-linux-scripting-Nechrito /home/philar-8/s0017d-1-linux-scripting-Nechrito /home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles/RealTimeEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RealTimeEngine.dir/depend
