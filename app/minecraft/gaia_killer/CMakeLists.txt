cmake_minimum_required (VERSION 3.23)

project("minecraft_gaia_killer")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Project target
add_executable(${PROJECT_NAME} "main.cpp")
