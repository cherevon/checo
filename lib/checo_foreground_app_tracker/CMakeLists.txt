cmake_minimum_required(VERSION 3.27)

project("checo_foreground_app_tracker")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Qt6 REQUIRED COMPONENTS Core)

# Include modules
include(GenerateExportHeader)

# Project targets
qt_wrap_cpp(SOURCES_MOC
	"include/checo/os/foreground_app_tracker.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	"src/checo/os/foreground_app_tracker.cpp"
)
add_library(checo::os::foreground_app_tracker ALIAS ${PROJECT_NAME})

# Project includes
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}_export.h")
target_include_directories(${PROJECT_NAME} PUBLIC "include")

# Link dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Core)