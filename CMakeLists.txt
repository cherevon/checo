cmake_minimum_required(VERSION 3.27)

project("checo")

# Options
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add libraries and projects listed in this repository
add_subdirectory("lib/checo_command_executor")
add_subdirectory("lib/checo_foreground_app_tracker")
add_subdirectory("lib/checo_os")
add_subdirectory("lib/checo_os_ui")
add_subdirectory("lib/checo_tile_view")
add_subdirectory("lib/checo_buttons")
add_subdirectory("lib/checo_dialogs")