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
CMAKE_SOURCE_DIR = /home/vincent/Bureau/PLT/antoine_justine_kuga_theau

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src

# Include any dependencies generated for this target.
include src/client/CMakeFiles/client_static.dir/depend.make

# Include the progress variables for this target.
include src/client/CMakeFiles/client_static.dir/progress.make

# Include the compile flags for this target's objects.
include src/client/CMakeFiles/client_static.dir/flags.make

src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o: src/client/CMakeFiles/client_static.dir/flags.make
src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o: client/client/Exemple.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_static.dir/client/Exemple.cpp.o -c /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/client/Exemple.cpp

src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_static.dir/client/Exemple.cpp.i"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/client/Exemple.cpp > CMakeFiles/client_static.dir/client/Exemple.cpp.i

src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_static.dir/client/Exemple.cpp.s"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/client/Exemple.cpp -o CMakeFiles/client_static.dir/client/Exemple.cpp.s

src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.requires:

.PHONY : src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.requires

src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.provides: src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.requires
	$(MAKE) -f src/client/CMakeFiles/client_static.dir/build.make src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.provides.build
.PHONY : src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.provides

src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.provides.build: src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o


src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o: src/client/CMakeFiles/client_static.dir/flags.make
src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o: client/render/StateLayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_static.dir/render/StateLayer.cpp.o -c /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/StateLayer.cpp

src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_static.dir/render/StateLayer.cpp.i"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/StateLayer.cpp > CMakeFiles/client_static.dir/render/StateLayer.cpp.i

src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_static.dir/render/StateLayer.cpp.s"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/StateLayer.cpp -o CMakeFiles/client_static.dir/render/StateLayer.cpp.s

src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.requires:

.PHONY : src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.requires

src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.provides: src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.requires
	$(MAKE) -f src/client/CMakeFiles/client_static.dir/build.make src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.provides.build
.PHONY : src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.provides

src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.provides.build: src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o


src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o: src/client/CMakeFiles/client_static.dir/flags.make
src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o: client/render/TextureArea.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_static.dir/render/TextureArea.cpp.o -c /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/TextureArea.cpp

src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_static.dir/render/TextureArea.cpp.i"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/TextureArea.cpp > CMakeFiles/client_static.dir/render/TextureArea.cpp.i

src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_static.dir/render/TextureArea.cpp.s"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/TextureArea.cpp -o CMakeFiles/client_static.dir/render/TextureArea.cpp.s

src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.requires:

.PHONY : src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.requires

src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.provides: src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.requires
	$(MAKE) -f src/client/CMakeFiles/client_static.dir/build.make src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.provides.build
.PHONY : src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.provides

src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.provides.build: src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o


src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o: src/client/CMakeFiles/client_static.dir/flags.make
src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o: client/render/TileSet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_static.dir/render/TileSet.cpp.o -c /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/TileSet.cpp

src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_static.dir/render/TileSet.cpp.i"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/TileSet.cpp > CMakeFiles/client_static.dir/render/TileSet.cpp.i

src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_static.dir/render/TileSet.cpp.s"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client/render/TileSet.cpp -o CMakeFiles/client_static.dir/render/TileSet.cpp.s

src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.requires:

.PHONY : src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.requires

src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.provides: src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.requires
	$(MAKE) -f src/client/CMakeFiles/client_static.dir/build.make src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.provides.build
.PHONY : src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.provides

src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.provides.build: src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o


# Object files for target client_static
client_static_OBJECTS = \
"CMakeFiles/client_static.dir/client/Exemple.cpp.o" \
"CMakeFiles/client_static.dir/render/StateLayer.cpp.o" \
"CMakeFiles/client_static.dir/render/TextureArea.cpp.o" \
"CMakeFiles/client_static.dir/render/TileSet.cpp.o"

# External object files for target client_static
client_static_EXTERNAL_OBJECTS =

src/client/libclient_static.a: src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o
src/client/libclient_static.a: src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o
src/client/libclient_static.a: src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o
src/client/libclient_static.a: src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o
src/client/libclient_static.a: src/client/CMakeFiles/client_static.dir/build.make
src/client/libclient_static.a: src/client/CMakeFiles/client_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libclient_static.a"
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && $(CMAKE_COMMAND) -P CMakeFiles/client_static.dir/cmake_clean_target.cmake
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/client/CMakeFiles/client_static.dir/build: src/client/libclient_static.a

.PHONY : src/client/CMakeFiles/client_static.dir/build

src/client/CMakeFiles/client_static.dir/requires: src/client/CMakeFiles/client_static.dir/client/Exemple.cpp.o.requires
src/client/CMakeFiles/client_static.dir/requires: src/client/CMakeFiles/client_static.dir/render/StateLayer.cpp.o.requires
src/client/CMakeFiles/client_static.dir/requires: src/client/CMakeFiles/client_static.dir/render/TextureArea.cpp.o.requires
src/client/CMakeFiles/client_static.dir/requires: src/client/CMakeFiles/client_static.dir/render/TileSet.cpp.o.requires

.PHONY : src/client/CMakeFiles/client_static.dir/requires

src/client/CMakeFiles/client_static.dir/clean:
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client && $(CMAKE_COMMAND) -P CMakeFiles/client_static.dir/cmake_clean.cmake
.PHONY : src/client/CMakeFiles/client_static.dir/clean

src/client/CMakeFiles/client_static.dir/depend:
	cd /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vincent/Bureau/PLT/antoine_justine_kuga_theau /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/client /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client /home/vincent/Bureau/PLT/antoine_justine_kuga_theau/src/src/client/CMakeFiles/client_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/client/CMakeFiles/client_static.dir/depend

