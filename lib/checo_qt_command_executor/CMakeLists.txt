cmake_minimum_required(VERSION 3.27)

project("checo_qt_command_executor")

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
add_library(${PROJECT_NAME}
	"src/command_executor.cpp"
	"src/complex_command_executor.cpp"
	"src/key_sequence_command_executor.cpp"
	"src/mouse_click_command_executor.cpp"
	"src/mouse_command_executor.cpp"
	"src/mouse_move_command_executor.cpp"
	"src/shutdown_command_executor.cpp"
	"src/start_application_command_executor.cpp"
	"src/terminate_application_command_executor.cpp"
	"src/toggle_window_command_executor.cpp"
	"src/type_text_command_executor.cpp"
)
add_library(checo::qt::command_executor ALIAS ${PROJECT_NAME})

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
		Qt::Widgets
)