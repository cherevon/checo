cmake_minimum_required(VERSION 3.27)

project("checo_tile_view")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include modules
include(GenerateExportHeader)

# Project targets
qt_wrap_ui(SOURCES_UI
	"ui/checo/ui/add_tile_dialog.ui"
)
qt_wrap_cpp(SOURCES_MOC
	"include/checo/ui/add_tile_dialog.h"
	"include/checo/ui/tile_table_model.h"
	"include/checo/ui/tile_view.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	${SOURCES_UI}
	"src/checo/ui/add_tile_dialog.cpp"
	"src/checo/ui/tile_delegate.cpp"
	"src/checo/ui/tile_table_model.cpp"
	"src/checo/ui/tile_view.cpp"
)
add_library(checo::ui::tile_view ALIAS ${PROJECT_NAME})

# Project includes
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}_export.h")
target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		"include"
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

# Project dependencies
target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		Qt::Widgets
		checo::ui::buttons
	PRIVATE
		checo::os::ui
)