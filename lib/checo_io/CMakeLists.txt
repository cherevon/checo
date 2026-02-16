cmake_minimum_required(VERSION 3.27)

project("checo_io")

# Project targets
add_library(${PROJECT_NAME} INTERFACE)
add_library(checo::io ALIAS ${PROJECT_NAME})

# Project includes
target_include_directories(${PROJECT_NAME} INTERFACE "include")
