cmake_minimum_required(VERSION 3.27)

project("checo_os")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Qt6 REQUIRED 
	COMPONENTS 
		Core
		Gui
		Widgets
)

# Include modules
include(GenerateExportHeader)

# Project targets
qt_wrap_cpp(SOURCES_MOC
	"include/checo/os/application_info_model.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	"src/checo/os/application_info.cpp"
	"src/checo/os/application_info_model.cpp"
)
add_library(checo::os ALIAS ${PROJECT_NAME})

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
		Qt::Core
		Qt::Gui
	PRIVATE
		comctl32
		Qt::Widgets
)