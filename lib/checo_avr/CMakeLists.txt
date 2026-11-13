cmake_minimum_required(VERSION 3.27)

project("checo_avr" LANGUAGES CXX)

# Project target
add_library(${PROJECT_NAME} INTERFACE)
add_library(checo::avr ALIAS ${PROJECT_NAME})

# Project compile settings
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

# Project includes
target_include_directories(${PROJECT_NAME} INTERFACE "include")
