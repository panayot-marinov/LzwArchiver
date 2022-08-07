set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.22.0)

project(LzwCompression)

add_subdirectory(compressor/byte)
add_subdirectory(compressor/directory)
add_subdirectory(compressor/file)
add_subdirectory(file)
add_subdirectory(path)
add_subdirectory(wordCode/reader)
add_subdirectory(wordCode/writer)
add_subdirectory(wordCode)

add_executable(${PROJECT_NAME} main.cpp compressor/byte/ByteCompressor.cpp compressor/directory/DirectoryCompressor.cpp compressor/file/FileCompressor.cpp file/File.cpp path/PathUtils.cpp wordCode/reader/WordCodeReader.cpp wordcode/writer/WordCodeWriter.cpp wordCode/WordCodeUtils.cpp)

target_link_libraries(${PROJECT_NAME} byteCompressor directoryCompressor fileCompressor file pathUtils wordCodeReader wordCodeWriter wordCodeUtils)
