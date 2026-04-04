cmake_minimum_required(VERSION 3.27)

project("checo")

# Options
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Add libraries listed in this repository
add_subdirectory("lib/checo_id")
add_subdirectory("lib/checo_io")
add_subdirectory("lib/checo_log")
