cmake_minimum_required(VERSION 3.27)

project("checo")

# Options
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Add libraries listed in this repository
add_subdirectory("lib/checo_logging")
add_subdirectory("lib/checo_qt")
add_subdirectory("lib/checo_qt_buttons")
add_subdirectory("lib/checo_qt_command_executor")
add_subdirectory("lib/checo_qt_dialogs")
add_subdirectory("lib/checo_qt_gui")
add_subdirectory("lib/checo_qt_widgets")

# Add applications listed in this repository
add_subdirectory("app/minecraft/auto_sell")
add_subdirectory("app/minecraft/gaia_killer")
add_subdirectory("app/rimworld/image_to_plan")