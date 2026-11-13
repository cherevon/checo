cmake_minimum_required(VERSION 3.27)

project("checo_game_engine" LANGUAGES CXX)

# Dependencies and modules
include(GenerateExportHeader)

# Project target
add_library(${PROJECT_NAME}
	"src/actor.cpp"
	"src/tag_component.cpp"
    "src/actor_component.cpp"
    "src/stat_component.cpp"
    "src/status_effect_component.cpp"
    "src/status_effect.cpp"
)
add_library(checo::game::engine ALIAS ${PROJECT_NAME})

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Target includes
set(GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/generated_include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${GENERATED_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC checo::core)

# Tests
if (${CHECO_ENABLE_TESTS})
    add_subdirectory("test")
endif()
