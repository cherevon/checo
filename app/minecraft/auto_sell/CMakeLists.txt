cmake_minimum_required (VERSION 3.23)

project("minecraft_auto_sell" LANGUAGES CXX)

# Project target
add_executable(${PROJECT_NAME} "main.cpp")

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
