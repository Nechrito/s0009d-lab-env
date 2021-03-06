# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/philar-8/s0017d-1-linux-scripting-Nechrito/projects/RealTimeEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/philar-8/s0017d-1-linux-scripting-Nechrito

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles /home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/philar-8/s0017d-1-linux-scripting-Nechrito/CMakeFiles 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named RealTimeEngine

# Build rule for target.
RealTimeEngine: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 RealTimeEngine
.PHONY : RealTimeEngine

# fast build rule for target.
RealTimeEngine/fast:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/build
.PHONY : RealTimeEngine/fast

# target to build an object file
code/Application.o:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Application.o
.PHONY : code/Application.o

# target to preprocess a source file
code/Application.i:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Application.i
.PHONY : code/Application.i

# target to generate assembly for a file
code/Application.s:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Application.s
.PHONY : code/Application.s

# target to build an object file
code/Camera.o:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Camera.o
.PHONY : code/Camera.o

# target to preprocess a source file
code/Camera.i:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Camera.i
.PHONY : code/Camera.i

# target to generate assembly for a file
code/Camera.s:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Camera.s
.PHONY : code/Camera.s

# target to build an object file
code/LightNode.o:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/LightNode.o
.PHONY : code/LightNode.o

# target to preprocess a source file
code/LightNode.i:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/LightNode.i
.PHONY : code/LightNode.i

# target to generate assembly for a file
code/LightNode.s:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/LightNode.s
.PHONY : code/LightNode.s

# target to build an object file
code/Model.o:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Model.o
.PHONY : code/Model.o

# target to preprocess a source file
code/Model.i:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Model.i
.PHONY : code/Model.i

# target to generate assembly for a file
code/Model.s:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Model.s
.PHONY : code/Model.s

# target to build an object file
code/RealTimeEngine.o:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.o
.PHONY : code/RealTimeEngine.o

# target to preprocess a source file
code/RealTimeEngine.i:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.i
.PHONY : code/RealTimeEngine.i

# target to generate assembly for a file
code/RealTimeEngine.s:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/RealTimeEngine.s
.PHONY : code/RealTimeEngine.s

# target to build an object file
code/SoftwareRenderer.o:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.o
.PHONY : code/SoftwareRenderer.o

# target to preprocess a source file
code/SoftwareRenderer.i:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.i
.PHONY : code/SoftwareRenderer.i

# target to generate assembly for a file
code/SoftwareRenderer.s:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/SoftwareRenderer.s
.PHONY : code/SoftwareRenderer.s

# target to build an object file
code/Transform.o:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Transform.o
.PHONY : code/Transform.o

# target to preprocess a source file
code/Transform.i:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Transform.i
.PHONY : code/Transform.i

# target to generate assembly for a file
code/Transform.s:
	$(MAKE) -f CMakeFiles/RealTimeEngine.dir/build.make CMakeFiles/RealTimeEngine.dir/code/Transform.s
.PHONY : code/Transform.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... RealTimeEngine"
	@echo "... edit_cache"
	@echo "... code/Application.o"
	@echo "... code/Application.i"
	@echo "... code/Application.s"
	@echo "... code/Camera.o"
	@echo "... code/Camera.i"
	@echo "... code/Camera.s"
	@echo "... code/LightNode.o"
	@echo "... code/LightNode.i"
	@echo "... code/LightNode.s"
	@echo "... code/Model.o"
	@echo "... code/Model.i"
	@echo "... code/Model.s"
	@echo "... code/RealTimeEngine.o"
	@echo "... code/RealTimeEngine.i"
	@echo "... code/RealTimeEngine.s"
	@echo "... code/SoftwareRenderer.o"
	@echo "... code/SoftwareRenderer.i"
	@echo "... code/SoftwareRenderer.s"
	@echo "... code/Transform.o"
	@echo "... code/Transform.i"
	@echo "... code/Transform.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

