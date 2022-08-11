set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.22.0)

project(LzwCompression)

add_subdirectory(command/executor)
add_subdirectory(command/parser)
add_subdirectory(command/utils)
add_subdirectory(compressor/byte)
add_subdirectory(compressor/directory)
add_subdirectory(compressor/file)
add_subdirectory(file)
add_subdirectory(file/hasher)
add_subdirectory(path)
add_subdirectory(wordCode/reader)
add_subdirectory(wordCode/writer)
add_subdirectory(wordCode)

add_executable(${PROJECT_NAME} main.cpp command/parser/CommandParser.cpp command/executor/CommandExecutor.cpp command/utils/ArrayUtils.cpp command/utils/CharArrUtils.cpp compressor/byte/ByteCompressor.cpp compressor/directory/DirectoryCompressor.cpp compressor/file/FileCompressor.cpp file/File.cpp file/hasher/FileHasher.cpp path/PathUtils.cpp wordCode/reader/WordCodeReader.cpp wordcode/writer/WordCodeWriter.cpp wordCode/WordCodeUtils.cpp)

target_link_libraries(${PROJECT_NAME} arrayUtils byteCompressor charArrUtils commandParser commandExecutor directoryCompressor file fileCompressor fileHasher pathUtils wordCodeReader wordCodeWriter wordCodeUtils)
