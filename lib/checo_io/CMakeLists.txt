cmake_minimum_required(VERSION 3.27)

project("checo_io" LANGUAGES CXX)

# Include modules
include(GenerateExportHeader)

# Project target
add_library(${PROJECT_NAME}
	"src/string_io.cpp"
)
add_library(checo::io ALIAS ${PROJECT_NAME})

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Target includes
set(GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/generated_include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${GENERATED_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Tests
if (${CHECO_ENABLE_TESTS})
	add_subdirectory("test")
endif()
