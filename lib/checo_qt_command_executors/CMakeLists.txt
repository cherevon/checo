cmake_minimum_required(VERSION 3.27)

project("checo_qt_command_executors" LANGUAGES CXX)

# Dependencies and modules
find_package(Qt6 REQUIRED 
	COMPONENTS 
		Core
		Gui
		Widgets
)
include(GenerateExportHeader)

# Project target
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
add_library(checo::qt::command_executors ALIAS ${PROJECT_NAME})

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
		Qt::Core 
		Qt::Gui
		Qt::Widgets
)