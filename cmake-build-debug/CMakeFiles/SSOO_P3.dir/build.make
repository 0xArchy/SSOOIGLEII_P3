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
CMAKE_SOURCE_DIR = /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SSOO_P3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SSOO_P3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SSOO_P3.dir/flags.make

CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o: CMakeFiles/SSOO_P3.dir/flags.make
CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o: ../src/Buscador.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o -c /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/src/Buscador.cpp

CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/src/Buscador.cpp > CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.i

CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/src/Buscador.cpp -o CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.s

CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.requires:

.PHONY : CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.requires

CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.provides: CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.requires
	$(MAKE) -f CMakeFiles/SSOO_P3.dir/build.make CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.provides.build
.PHONY : CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.provides

CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.provides.build: CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o


CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o: CMakeFiles/SSOO_P3.dir/flags.make
CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o: ../src/semaphoreI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o -c /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/src/semaphoreI.cpp

CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/src/semaphoreI.cpp > CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.i

CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/src/semaphoreI.cpp -o CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.s

CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.requires:

.PHONY : CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.requires

CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.provides: CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.requires
	$(MAKE) -f CMakeFiles/SSOO_P3.dir/build.make CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.provides.build
.PHONY : CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.provides

CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.provides.build: CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o


# Object files for target SSOO_P3
SSOO_P3_OBJECTS = \
"CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o" \
"CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o"

# External object files for target SSOO_P3
SSOO_P3_EXTERNAL_OBJECTS =

SSOO_P3: CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o
SSOO_P3: CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o
SSOO_P3: CMakeFiles/SSOO_P3.dir/build.make
SSOO_P3: CMakeFiles/SSOO_P3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SSOO_P3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SSOO_P3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SSOO_P3.dir/build: SSOO_P3

.PHONY : CMakeFiles/SSOO_P3.dir/build

CMakeFiles/SSOO_P3.dir/requires: CMakeFiles/SSOO_P3.dir/src/Buscador.cpp.o.requires
CMakeFiles/SSOO_P3.dir/requires: CMakeFiles/SSOO_P3.dir/src/semaphoreI.cpp.o.requires

.PHONY : CMakeFiles/SSOO_P3.dir/requires

CMakeFiles/SSOO_P3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SSOO_P3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SSOO_P3.dir/clean

CMakeFiles/SSOO_P3.dir/depend:
	cd /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3 /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3 /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug /mnt/c/Users/TOMIC/CLionProjects/SSOO_P3/cmake-build-debug/CMakeFiles/SSOO_P3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SSOO_P3.dir/depend

