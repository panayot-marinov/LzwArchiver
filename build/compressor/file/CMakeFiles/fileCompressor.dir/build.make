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
include compressor/file/CMakeFiles/fileCompressor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include compressor/file/CMakeFiles/fileCompressor.dir/compiler_depend.make

# Include the progress variables for this target.
include compressor/file/CMakeFiles/fileCompressor.dir/progress.make

# Include the compile flags for this target's objects.
include compressor/file/CMakeFiles/fileCompressor.dir/flags.make

compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.obj: compressor/file/CMakeFiles/fileCompressor.dir/flags.make
compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.obj: C:/Users/Panayot\ Marinov/Desktop/FMI\ 2021/SDP/Project/LzwArchiver/ConsoleApp/src/compressor/file/FileCompressor.cpp
compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.obj: compressor/file/CMakeFiles/fileCompressor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.obj"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\COMPRE~1\file && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.obj -MF CMakeFiles\fileCompressor.dir\FileCompressor.cpp.obj.d -o CMakeFiles\fileCompressor.dir\FileCompressor.cpp.obj -c "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\compressor\file\FileCompressor.cpp"

compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fileCompressor.dir/FileCompressor.cpp.i"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\COMPRE~1\file && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\compressor\file\FileCompressor.cpp" > CMakeFiles\fileCompressor.dir\FileCompressor.cpp.i

compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fileCompressor.dir/FileCompressor.cpp.s"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\COMPRE~1\file && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\compressor\file\FileCompressor.cpp" -o CMakeFiles\fileCompressor.dir\FileCompressor.cpp.s

# Object files for target fileCompressor
fileCompressor_OBJECTS = \
"CMakeFiles/fileCompressor.dir/FileCompressor.cpp.obj"

# External object files for target fileCompressor
fileCompressor_EXTERNAL_OBJECTS =

compressor/file/libfileCompressor.a: compressor/file/CMakeFiles/fileCompressor.dir/FileCompressor.cpp.obj
compressor/file/libfileCompressor.a: compressor/file/CMakeFiles/fileCompressor.dir/build.make
compressor/file/libfileCompressor.a: compressor/file/CMakeFiles/fileCompressor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libfileCompressor.a"
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\COMPRE~1\file && $(CMAKE_COMMAND) -P CMakeFiles\fileCompressor.dir\cmake_clean_target.cmake
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\COMPRE~1\file && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\fileCompressor.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
compressor/file/CMakeFiles/fileCompressor.dir/build: compressor/file/libfileCompressor.a
.PHONY : compressor/file/CMakeFiles/fileCompressor.dir/build

compressor/file/CMakeFiles/fileCompressor.dir/clean:
	cd /d C:\Users\PANAYO~1\Desktop\FMI202~1\SDP\Project\LZWARC~1\build\COMPRE~1\file && $(CMAKE_COMMAND) -P CMakeFiles\fileCompressor.dir\cmake_clean.cmake
.PHONY : compressor/file/CMakeFiles/fileCompressor.dir/clean

compressor/file/CMakeFiles/fileCompressor.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\ConsoleApp\src\compressor\file" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\compressor\file" "C:\Users\Panayot Marinov\Desktop\FMI 2021\SDP\Project\LzwArchiver\build\compressor\file\CMakeFiles\fileCompressor.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : compressor/file/CMakeFiles/fileCompressor.dir/depend

