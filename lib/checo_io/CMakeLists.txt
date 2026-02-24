cmake_minimum_required(VERSION 3.27)

project("checo_io")

# Project targets
add_library(${PROJECT_NAME}
	"src/string_io.cpp"
)
add_library(checo::io ALIAS ${PROJECT_NAME})

# Project includes
set(PROJECT_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_GENERATED_INCLUDE_DIR}
		"include"
)

# Tests
if (${CHECO_ENABLE_TESTS})
	add_subdirectory("test")
endif()
