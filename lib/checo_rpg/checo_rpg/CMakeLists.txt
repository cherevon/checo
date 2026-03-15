cmake_minimum_required(VERSION 3.27)

project("checo_rpg")

# Include modules
include(GenerateExportHeader)

# Project targets
add_library(${PROJECT_NAME}
	"src/lib_export_symbols.cpp"
)
add_library(checo::rpg ALIAS ${PROJECT_NAME})

# Project includes
set(PROJECT_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_GENERATED_INCLUDE_DIR}
		"include"
)
