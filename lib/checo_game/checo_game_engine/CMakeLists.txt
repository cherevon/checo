cmake_minimum_required(VERSION 3.27)

project("checo_game_engine" LANGUAGES CXX)

# Project target
add_library(${PROJECT_NAME} STATIC
	"src/tag_component.cpp"
    "src/stat_component.cpp"
)
add_library(checo::game::engine ALIAS ${PROJECT_NAME})

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Target includes
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Tests
if (${CHECO_ENABLE_TESTS})
    add_subdirectory("test")
endif()
