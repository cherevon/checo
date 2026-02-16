cmake_minimum_required(VERSION 3.27)

project("checo_qt_buttons")

# Find dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include modules
include(GenerateExportHeader)

# Project targets
qt_wrap_cpp(SOURCES_MOC
	"include/checo/qt/multi_icon_button.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	"src/multi_icon_button.cpp"
)
add_library(checo::qt::buttons ALIAS ${PROJECT_NAME})

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
target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Widgets)
