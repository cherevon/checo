cmake_minimum_required(VERSION 3.27)

project("checo_qt_gui" LANGUAGES CXX)

# Dependencies and modules
find_package(Qt6 REQUIRED 
	COMPONENTS 
		Core
		Gui
		Widgets
)
include(GenerateExportHeader)

# Project target
qt_wrap_cpp(SOURCES_MOC
	"include/checo/qt/application_info_model.h"
)
add_library(${PROJECT_NAME}
	${SOURCES_MOC}
	"src/application_info.cpp"
	"src/application_info_model.cpp"
)
add_library(checo::qt::gui ALIAS ${PROJECT_NAME})

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
	PRIVATE
		$<$<PLATFORM_ID:Windows>:comctl32>
)