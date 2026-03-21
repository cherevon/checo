cmake_minimum_required(VERSION 3.27)

project("checo_rpg_test_support")

# Include modules
include(GenerateExportHeader)

# Project targets
add_library(${PROJECT_NAME}
    "src/ability_test_support.cpp"
    "src/character_test_support.cpp"
    "src/currency_test_support.cpp"
    "src/inventory_test_support.cpp"
    "src/item_test_support.cpp"
    "src/stat_test_support.cpp"
    "src/status_effect_test_support.cpp"
    "src/entity_test_support.cpp"
    "src/test_support.cpp"
)
add_library(checo::rpg::test_support ALIAS ${PROJECT_NAME})

# Project includes
set(PROJECT_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_GENERATED_INCLUDE_DIR}
		"include"
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC checo::rpg)
