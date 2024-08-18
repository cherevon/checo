cmake_minimum_required(VERSION 3.27)

project("checo_command_executor")

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
	"src/checo/command_executor/complex_command_executor.cpp"
	#"src/checo/command_executor/command_executor_factory.cpp"
	"src/checo/command_executor/key_sequence.cpp"
	"src/checo/command_executor/mouse.cpp"
	"src/checo/command_executor/mouse_click.cpp"
	"src/checo/command_executor/mouse_move.cpp"
	"src/checo/command_executor/shutdown.cpp"
	"src/checo/command_executor/start_application.cpp"
	"src/checo/command_executor/terminate_application.cpp"
	"src/checo/command_executor/toggle_window.cpp"
	"src/checo/command_executor/type_text.cpp"
)
add_library(checo::command_executor ALIAS ${PROJECT_NAME})

# Project includes
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}_export.h")
target_include_directories(${PROJECT_NAME} PUBLIC "include")

# Link dependencies
target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		checo::os
		Qt::Core 
		Qt::Gui
		Qt::Widgets
)