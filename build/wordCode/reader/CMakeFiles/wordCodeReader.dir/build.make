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
CMAKE_SOURCE_DIR = "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build"

# Include any dependencies generated for this target.
include wordCode/reader/CMakeFiles/wordCodeReader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include wordCode/reader/CMakeFiles/wordCodeReader.dir/compiler_depend.make

# Include the progress variables for this target.
include wordCode/reader/CMakeFiles/wordCodeReader.dir/progress.make

# Include the compile flags for this target's objects.
include wordCode/reader/CMakeFiles/wordCodeReader.dir/flags.make

wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.obj: wordCode/reader/CMakeFiles/wordCodeReader.dir/flags.make
wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.obj: C:/Users/Panayot\ Marinov/Desktop/FMI\ 2021/SDP/Project/LzwArchiver/ConsoleApp/src/wordCode/reader/WordCodeReader.cpp
wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.obj: wordCode/reader/CMakeFiles/wordCodeReader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.obj"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\wordCode\reader && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.obj -MF CMakeFiles\wordCodeReader.dir\WordCodeReader.cpp.obj.d -o CMakeFiles\wordCodeReader.dir\WordCodeReader.cpp.obj -c "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\wordCode\reader\WordCodeReader.cpp"

wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.i"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\wordCode\reader && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\wordCode\reader\WordCodeReader.cpp" > CMakeFiles\wordCodeReader.dir\WordCodeReader.cpp.i

wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.s"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\wordCode\reader && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\wordCode\reader\WordCodeReader.cpp" -o CMakeFiles\wordCodeReader.dir\WordCodeReader.cpp.s

# Object files for target wordCodeReader
wordCodeReader_OBJECTS = \
"CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.obj"

# External object files for target wordCodeReader
wordCodeReader_EXTERNAL_OBJECTS =

wordCode/reader/libwordCodeReader.a: wordCode/reader/CMakeFiles/wordCodeReader.dir/WordCodeReader.cpp.obj
wordCode/reader/libwordCodeReader.a: wordCode/reader/CMakeFiles/wordCodeReader.dir/build.make
wordCode/reader/libwordCodeReader.a: wordCode/reader/CMakeFiles/wordCodeReader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libwordCodeReader.a"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\wordCode\reader && $(CMAKE_COMMAND) -P CMakeFiles\wordCodeReader.dir\cmake_clean_target.cmake
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\wordCode\reader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\wordCodeReader.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
wordCode/reader/CMakeFiles/wordCodeReader.dir/build: wordCode/reader/libwordCodeReader.a
.PHONY : wordCode/reader/CMakeFiles/wordCodeReader.dir/build

wordCode/reader/CMakeFiles/wordCodeReader.dir/clean:
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\wordCode\reader && $(CMAKE_COMMAND) -P CMakeFiles\wordCodeReader.dir\cmake_clean.cmake
.PHONY : wordCode/reader/CMakeFiles/wordCodeReader.dir/clean

wordCode/reader/CMakeFiles/wordCodeReader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\wordCode\reader" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\wordCode\reader" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\wordCode\reader\CMakeFiles\wordCodeReader.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : wordCode/reader/CMakeFiles/wordCodeReader.dir/depend

