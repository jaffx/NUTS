# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lyn/codes/Cpp/clion/NUTS/nuts

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lyn/codes/Cpp/clion/NUTS/nuts/build

# Include any dependencies generated for this target.
include CMakeFiles/nuts_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/nuts_static.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nuts_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nuts_static.dir/flags.make

CMakeFiles/nuts_static.dir/src/basic.cpp.o: CMakeFiles/nuts_static.dir/flags.make
CMakeFiles/nuts_static.dir/src/basic.cpp.o: /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/basic.cpp
CMakeFiles/nuts_static.dir/src/basic.cpp.o: CMakeFiles/nuts_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nuts_static.dir/src/basic.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nuts_static.dir/src/basic.cpp.o -MF CMakeFiles/nuts_static.dir/src/basic.cpp.o.d -o CMakeFiles/nuts_static.dir/src/basic.cpp.o -c /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/basic.cpp

CMakeFiles/nuts_static.dir/src/basic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuts_static.dir/src/basic.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/basic.cpp > CMakeFiles/nuts_static.dir/src/basic.cpp.i

CMakeFiles/nuts_static.dir/src/basic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuts_static.dir/src/basic.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/basic.cpp -o CMakeFiles/nuts_static.dir/src/basic.cpp.s

CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o: CMakeFiles/nuts_static.dir/flags.make
CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o: /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_client.cpp
CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o: CMakeFiles/nuts_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o -MF CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o.d -o CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o -c /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_client.cpp

CMakeFiles/nuts_static.dir/src/nuts_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuts_static.dir/src/nuts_client.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_client.cpp > CMakeFiles/nuts_static.dir/src/nuts_client.cpp.i

CMakeFiles/nuts_static.dir/src/nuts_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuts_static.dir/src/nuts_client.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_client.cpp -o CMakeFiles/nuts_static.dir/src/nuts_client.cpp.s

CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o: CMakeFiles/nuts_static.dir/flags.make
CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o: /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_server.cpp
CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o: CMakeFiles/nuts_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o -MF CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o.d -o CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o -c /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_server.cpp

CMakeFiles/nuts_static.dir/src/nuts_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuts_static.dir/src/nuts_server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_server.cpp > CMakeFiles/nuts_static.dir/src/nuts_server.cpp.i

CMakeFiles/nuts_static.dir/src/nuts_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuts_static.dir/src/nuts_server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_server.cpp -o CMakeFiles/nuts_static.dir/src/nuts_server.cpp.s

CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o: CMakeFiles/nuts_static.dir/flags.make
CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o: /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_datagram.cpp
CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o: CMakeFiles/nuts_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o -MF CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o.d -o CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o -c /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_datagram.cpp

CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_datagram.cpp > CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.i

CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_datagram.cpp -o CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.s

CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o: CMakeFiles/nuts_static.dir/flags.make
CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o: /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_center.cpp
CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o: CMakeFiles/nuts_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o -MF CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o.d -o CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o -c /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_center.cpp

CMakeFiles/nuts_static.dir/src/nuts_center.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuts_static.dir/src/nuts_center.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_center.cpp > CMakeFiles/nuts_static.dir/src/nuts_center.cpp.i

CMakeFiles/nuts_static.dir/src/nuts_center.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuts_static.dir/src/nuts_center.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/nuts_center.cpp -o CMakeFiles/nuts_static.dir/src/nuts_center.cpp.s

CMakeFiles/nuts_static.dir/src/order_tree.cpp.o: CMakeFiles/nuts_static.dir/flags.make
CMakeFiles/nuts_static.dir/src/order_tree.cpp.o: /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/order_tree.cpp
CMakeFiles/nuts_static.dir/src/order_tree.cpp.o: CMakeFiles/nuts_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/nuts_static.dir/src/order_tree.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nuts_static.dir/src/order_tree.cpp.o -MF CMakeFiles/nuts_static.dir/src/order_tree.cpp.o.d -o CMakeFiles/nuts_static.dir/src/order_tree.cpp.o -c /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/order_tree.cpp

CMakeFiles/nuts_static.dir/src/order_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuts_static.dir/src/order_tree.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/order_tree.cpp > CMakeFiles/nuts_static.dir/src/order_tree.cpp.i

CMakeFiles/nuts_static.dir/src/order_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuts_static.dir/src/order_tree.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lyn/codes/Cpp/clion/NUTS/nuts/src/order_tree.cpp -o CMakeFiles/nuts_static.dir/src/order_tree.cpp.s

# Object files for target nuts_static
nuts_static_OBJECTS = \
"CMakeFiles/nuts_static.dir/src/basic.cpp.o" \
"CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o" \
"CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o" \
"CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o" \
"CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o" \
"CMakeFiles/nuts_static.dir/src/order_tree.cpp.o"

# External object files for target nuts_static
nuts_static_EXTERNAL_OBJECTS =

/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/src/basic.cpp.o
/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/src/nuts_client.cpp.o
/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/src/nuts_server.cpp.o
/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/src/nuts_datagram.cpp.o
/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/src/nuts_center.cpp.o
/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/src/order_tree.cpp.o
/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/build.make
/Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a: CMakeFiles/nuts_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library /Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a"
	$(CMAKE_COMMAND) -P CMakeFiles/nuts_static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nuts_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nuts_static.dir/build: /Users/lyn/codes/Cpp/clion/NUTS/nuts/lib/libnuts.a
.PHONY : CMakeFiles/nuts_static.dir/build

CMakeFiles/nuts_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nuts_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nuts_static.dir/clean

CMakeFiles/nuts_static.dir/depend:
	cd /Users/lyn/codes/Cpp/clion/NUTS/nuts/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lyn/codes/Cpp/clion/NUTS/nuts /Users/lyn/codes/Cpp/clion/NUTS/nuts /Users/lyn/codes/Cpp/clion/NUTS/nuts/build /Users/lyn/codes/Cpp/clion/NUTS/nuts/build /Users/lyn/codes/Cpp/clion/NUTS/nuts/build/CMakeFiles/nuts_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nuts_static.dir/depend

