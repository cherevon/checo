cmake_minimum_required(VERSION 3.27)

project("checo_rpg_libs")

# Add libraries listed in this group
add_subdirectory("checo_rpg")
add_subdirectory("checo_rpg_io")

# Add libraries to support testing
if (${CHECO_ENABLE_TESTS})
    add_subdirectory("checo_rpg_test_support")
endif()
