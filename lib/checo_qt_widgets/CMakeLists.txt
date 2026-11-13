cmake_minimum_required(VERSION 3.27)

project("checo_qt_widgets" LANGUAGES CXX)

# Dependencies and modules
find_package(Qt6 REQUIRED COMPONENTS Widgets)
include(GenerateExportHeader)

# Project target
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
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::qt::gui
		Qt::Widgets
)
