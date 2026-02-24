cmake_minimum_required(VERSION 3.27)

project("checo_rpg_io")

# Include modules
include(GenerateExportHeader)

# Project targets
add_library(${PROJECT_NAME}
	"src/character_io.cpp"
	"src/entity_io.cpp"
	"src/inventory_io.cpp"
	"src/item_io.cpp"
)
add_library(checo::rpg::io ALIAS ${PROJECT_NAME})

# Project includes
set(PROJECT_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_GENERATED_INCLUDE_DIR}
		"include"
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::io
		checo::rpg
)
