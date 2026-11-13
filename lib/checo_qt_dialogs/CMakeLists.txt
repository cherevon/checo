cmake_minimum_required(VERSION 3.27)

project("checo_qt_dialogs" LANGUAGES CXX)

# Dependencies and modules
find_package(Qt6 REQUIRED COMPONENTS Widgets)
include(GenerateExportHeader)

# Project target
qt_wrap_ui(SOURCES_UI
	"ui/add_tile_dialog.ui"
	"ui/key_sequence_edit_dialog.ui"
	"ui/select_list_item_dialog.ui"
	"ui/text_edit_dialog.ui"
)
qt_wrap_cpp(SOURCES_MOC
	"include/checo/qt/add_tile_dialog.h"
	"include/checo/qt/key_sequence_edit_dialog.h"
	"include/checo/qt/overlay_dialog.h"
	"include/checo/qt/select_application_dialog.h"
	"include/checo/qt/select_list_item_dialog.h"
	"include/checo/qt/text_edit_dialog.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	${SOURCES_UI}
	"src/add_tile_dialog.cpp"
	"src/key_sequence_edit_dialog.cpp"
	"src/overlay_dialog.cpp"
	"src/select_application_dialog.cpp"
	"src/select_list_item_dialog.cpp"
	"src/text_edit_dialog.cpp"
)
add_library(checo::qt::dialogs ALIAS ${PROJECT_NAME})

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Target includes
set(GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/generated_include")
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${GENERATED_INCLUDE_DIR}/${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${GENERATED_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# Project dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::qt::buttons
		checo::qt::widgets
		Qt::Widgets
)
