cmake_minimum_required(VERSION 3.27)

project("checo_math")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project targets
add_library(${PROJECT_NAME} INTERFACE)
add_library(checo::math ALIAS ${PROJECT_NAME})

# Project includes
target_include_directories(${PROJECT_NAME} INTERFACE "include")

# Tests
if (CHECO_ENABLE_TESTS)
    add_subdirectory("test")
endif()