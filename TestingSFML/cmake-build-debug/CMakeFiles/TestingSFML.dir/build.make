# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\chess\CLionProjects\TestingSFML

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\chess\CLionProjects\TestingSFML\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TestingSFML.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestingSFML.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestingSFML.dir/flags.make

CMakeFiles/TestingSFML.dir/main.cpp.obj: CMakeFiles/TestingSFML.dir/flags.make
CMakeFiles/TestingSFML.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\chess\CLionProjects\TestingSFML\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestingSFML.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TestingSFML.dir\main.cpp.obj -c C:\Users\chess\CLionProjects\TestingSFML\main.cpp

CMakeFiles/TestingSFML.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestingSFML.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\chess\CLionProjects\TestingSFML\main.cpp > CMakeFiles\TestingSFML.dir\main.cpp.i

CMakeFiles/TestingSFML.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestingSFML.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\chess\CLionProjects\TestingSFML\main.cpp -o CMakeFiles\TestingSFML.dir\main.cpp.s

# Object files for target TestingSFML
TestingSFML_OBJECTS = \
"CMakeFiles/TestingSFML.dir/main.cpp.obj"

# External object files for target TestingSFML
TestingSFML_EXTERNAL_OBJECTS =

TestingSFML.exe: CMakeFiles/TestingSFML.dir/main.cpp.obj
TestingSFML.exe: CMakeFiles/TestingSFML.dir/build.make
TestingSFML.exe: CMakeFiles/TestingSFML.dir/linklibs.rsp
TestingSFML.exe: CMakeFiles/TestingSFML.dir/objects1.rsp
TestingSFML.exe: CMakeFiles/TestingSFML.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\chess\CLionProjects\TestingSFML\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestingSFML.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TestingSFML.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestingSFML.dir/build: TestingSFML.exe

.PHONY : CMakeFiles/TestingSFML.dir/build

CMakeFiles/TestingSFML.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TestingSFML.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TestingSFML.dir/clean

CMakeFiles/TestingSFML.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\chess\CLionProjects\TestingSFML C:\Users\chess\CLionProjects\TestingSFML C:\Users\chess\CLionProjects\TestingSFML\cmake-build-debug C:\Users\chess\CLionProjects\TestingSFML\cmake-build-debug C:\Users\chess\CLionProjects\TestingSFML\cmake-build-debug\CMakeFiles\TestingSFML.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestingSFML.dir/depend
