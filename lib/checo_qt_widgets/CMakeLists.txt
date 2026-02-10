cmake_minimum_required(VERSION 3.27)

project("checo_qt_widgets")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include modules
include(GenerateExportHeader)

# Project targets
qt_wrap_cpp(SOURCES_MOC
	"include/checo/qt/tile_table_model.h"
	"include/checo/qt/tile_view.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	"src/tile_delegate.cpp"
	"src/tile_table_model.cpp"
	"src/tile_view.cpp"
)
add_library(checo::qt::widgets ALIAS ${PROJECT_NAME})

# Project includes
set(PROJECT_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		${PROJECT_GENERATED_INCLUDE_DIR}
		"include"
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

# Project dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::qt::gui
		Qt::Widgets
)
