cmake_minimum_required(VERSION 3.5)
project(SYNAPSE_IN_THE_VOID VERSION 0.1 LANGUAGES C)

# header location
include_directories(include)

# fetch all .c files in src/
file(GLOB SRC_FILES src/*.c)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/testingbuffer.c)

# output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY      ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY      ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY      ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/symbols)
set(CMAKE_PDB_OUTPUT_DIRECTORY          ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/symbols)

# build the executable from ALL .c files
add_executable(${PROJECT_NAME} ${SRC_FILES})
