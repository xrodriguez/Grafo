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
CMAKE_SOURCE_DIR = /home/jose/Escritorio/2017-1/algoritmo/FinalProyect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jose/Escritorio/2017-1/algoritmo/FinalProyect

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jose/Escritorio/2017-1/algoritmo/FinalProyect/CMakeFiles /home/jose/Escritorio/2017-1/algoritmo/FinalProyect/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jose/Escritorio/2017-1/algoritmo/FinalProyect/CMakeFiles 0
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
# Target rules for targets named sfml-app

# Build rule for target.
sfml-app: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 sfml-app
.PHONY : sfml-app

# fast build rule for target.
sfml-app/fast:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/build
.PHONY : sfml-app/fast

Edge.o: Edge.cpp.o

.PHONY : Edge.o

# target to build an object file
Edge.cpp.o:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Edge.cpp.o
.PHONY : Edge.cpp.o

Edge.i: Edge.cpp.i

.PHONY : Edge.i

# target to preprocess a source file
Edge.cpp.i:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Edge.cpp.i
.PHONY : Edge.cpp.i

Edge.s: Edge.cpp.s

.PHONY : Edge.s

# target to generate assembly for a file
Edge.cpp.s:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Edge.cpp.s
.PHONY : Edge.cpp.s

Graph.o: Graph.cpp.o

.PHONY : Graph.o

# target to build an object file
Graph.cpp.o:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Graph.cpp.o
.PHONY : Graph.cpp.o

Graph.i: Graph.cpp.i

.PHONY : Graph.i

# target to preprocess a source file
Graph.cpp.i:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Graph.cpp.i
.PHONY : Graph.cpp.i

Graph.s: Graph.cpp.s

.PHONY : Graph.s

# target to generate assembly for a file
Graph.cpp.s:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Graph.cpp.s
.PHONY : Graph.cpp.s

Heuristics.o: Heuristics.cpp.o

.PHONY : Heuristics.o

# target to build an object file
Heuristics.cpp.o:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Heuristics.cpp.o
.PHONY : Heuristics.cpp.o

Heuristics.i: Heuristics.cpp.i

.PHONY : Heuristics.i

# target to preprocess a source file
Heuristics.cpp.i:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Heuristics.cpp.i
.PHONY : Heuristics.cpp.i

Heuristics.s: Heuristics.cpp.s

.PHONY : Heuristics.s

# target to generate assembly for a file
Heuristics.cpp.s:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Heuristics.cpp.s
.PHONY : Heuristics.cpp.s

Node.o: Node.cpp.o

.PHONY : Node.o

# target to build an object file
Node.cpp.o:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Node.cpp.o
.PHONY : Node.cpp.o

Node.i: Node.cpp.i

.PHONY : Node.i

# target to preprocess a source file
Node.cpp.i:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Node.cpp.i
.PHONY : Node.cpp.i

Node.s: Node.cpp.s

.PHONY : Node.s

# target to generate assembly for a file
Node.cpp.s:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/Node.cpp.s
.PHONY : Node.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/sfml-app.dir/build.make CMakeFiles/sfml-app.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... sfml-app"
	@echo "... Edge.o"
	@echo "... Edge.i"
	@echo "... Edge.s"
	@echo "... Graph.o"
	@echo "... Graph.i"
	@echo "... Graph.s"
	@echo "... Heuristics.o"
	@echo "... Heuristics.i"
	@echo "... Heuristics.s"
	@echo "... Node.o"
	@echo "... Node.i"
	@echo "... Node.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

