cmake_minimum_required(VERSION 3.27)

project("checo_dialogs")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include modules
include(GenerateExportHeader)

# Project targets
qt_wrap_ui(SOURCES_UI
	"ui/checo/ui/key_sequence_edit_dialog.ui"
	"ui/checo/ui/select_list_item_dialog.ui"
	"ui/checo/ui/text_edit_dialog.ui"
)
qt_wrap_cpp(SOURCES_MOC
	"include/checo/ui/key_sequence_edit_dialog.h"
	"include/checo/ui/overlay_dialog.h"
	"include/checo/ui/select_list_item_dialog.h"
	"include/checo/ui/text_edit_dialog.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	${SOURCES_UI}
	"src/checo/ui/key_sequence_edit_dialog.cpp"
	"src/checo/ui/overlay_dialog.cpp"
	"src/checo/ui/select_list_item_dialog.cpp"
	"src/checo/ui/text_edit_dialog.cpp"
)
add_library(checo::ui::dialogs ALIAS ${PROJECT_NAME})

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
		Qt::Widgets
	PRIVATE
		checo::ui::buttons
)