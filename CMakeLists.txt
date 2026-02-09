cmake_minimum_required(VERSION 3.27)

project("checo")

# Options
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Add libraries and projects listed in this repository
add_subdirectory("lib/checo_buttons")
add_subdirectory("lib/checo_command_executor")
add_subdirectory("lib/checo_dialogs")
add_subdirectory("lib/checo_foreground_app_tracker")
add_subdirectory("lib/checo_os")
add_subdirectory("lib/checo_os_ui")
add_subdirectory("lib/checo_tile_view")

# Add applications listed in this repository
add_subdirectory("app/minecraft/auto_sell")
add_subdirectory("app/minecraft/gaia_killer")
add_subdirectory("app/rimworld/image_to_plan")