# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\out\build"

# Include any dependencies generated for this target.
include reader/CMakeFiles/FileReader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include reader/CMakeFiles/FileReader.dir/compiler_depend.make

# Include the progress variables for this target.
include reader/CMakeFiles/FileReader.dir/progress.make

# Include the compile flags for this target's objects.
include reader/CMakeFiles/FileReader.dir/flags.make

reader/CMakeFiles/FileReader.dir/FileReader.cpp.obj: reader/CMakeFiles/FileReader.dir/flags.make
reader/CMakeFiles/FileReader.dir/FileReader.cpp.obj: C:/Users/Panayot\ Marinov/Desktop/FMI\ 2021/SDP/Project/LzwCompression/ConsoleApp/src/reader/FileReader.cpp
reader/CMakeFiles/FileReader.dir/FileReader.cpp.obj: reader/CMakeFiles/FileReader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\out\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object reader/CMakeFiles/FileReader.dir/FileReader.cpp.obj"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWCOM~1\CONSOL~1\out\build\reader && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT reader/CMakeFiles/FileReader.dir/FileReader.cpp.obj -MF CMakeFiles\FileReader.dir\FileReader.cpp.obj.d -o CMakeFiles\FileReader.dir\FileReader.cpp.obj -c "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\src\reader\FileReader.cpp"

reader/CMakeFiles/FileReader.dir/FileReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FileReader.dir/FileReader.cpp.i"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWCOM~1\CONSOL~1\out\build\reader && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\src\reader\FileReader.cpp" > CMakeFiles\FileReader.dir\FileReader.cpp.i

reader/CMakeFiles/FileReader.dir/FileReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FileReader.dir/FileReader.cpp.s"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWCOM~1\CONSOL~1\out\build\reader && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\src\reader\FileReader.cpp" -o CMakeFiles\FileReader.dir\FileReader.cpp.s

# Object files for target FileReader
FileReader_OBJECTS = \
"CMakeFiles/FileReader.dir/FileReader.cpp.obj"

# External object files for target FileReader
FileReader_EXTERNAL_OBJECTS =

reader/libFileReader.a: reader/CMakeFiles/FileReader.dir/FileReader.cpp.obj
reader/libFileReader.a: reader/CMakeFiles/FileReader.dir/build.make
reader/libFileReader.a: reader/CMakeFiles/FileReader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\out\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libFileReader.a"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWCOM~1\CONSOL~1\out\build\reader && $(CMAKE_COMMAND) -P CMakeFiles\FileReader.dir\cmake_clean_target.cmake
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWCOM~1\CONSOL~1\out\build\reader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\FileReader.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
reader/CMakeFiles/FileReader.dir/build: reader/libFileReader.a
.PHONY : reader/CMakeFiles/FileReader.dir/build

reader/CMakeFiles/FileReader.dir/clean:
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWCOM~1\CONSOL~1\out\build\reader && $(CMAKE_COMMAND) -P CMakeFiles\FileReader.dir\cmake_clean.cmake
.PHONY : reader/CMakeFiles/FileReader.dir/clean

reader/CMakeFiles/FileReader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\src" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\src\reader" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\out\build" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\out\build\reader" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwCompression\ConsoleApp\out\build\reader\CMakeFiles\FileReader.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : reader/CMakeFiles/FileReader.dir/depend

