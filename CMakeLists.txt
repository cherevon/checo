cmake_minimum_required(VERSION 3.27)

project("checo_repo" LANGUAGES CXX)

# Options
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Add applications listed in this repository
add_subdirectory("app/minecraft/auto_clicker")
add_subdirectory("app/minecraft/auto_sell")
add_subdirectory("app/minecraft/gaia_killer")
add_subdirectory("app/rimworld/image_to_plan")

# Add libraries listed in this repository
add_subdirectory("lib/checo_game/checo_game_engine")
add_subdirectory("lib/checo_game/checo_game_rpg")
add_subdirectory("lib/checo_id")
add_subdirectory("lib/checo_io")
add_subdirectory("lib/checo_log")
add_subdirectory("lib/checo_qt")
add_subdirectory("lib/checo_qt_buttons")
add_subdirectory("lib/checo_qt_command_executors")
add_subdirectory("lib/checo_qt_dialogs")
add_subdirectory("lib/checo_qt_gui")
add_subdirectory("lib/checo_qt_widgets")
