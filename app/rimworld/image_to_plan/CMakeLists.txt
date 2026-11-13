cmake_minimum_required(VERSION 3.27)

project("rimworld_image_to_plan" LANGUAGES CXX)

# Dependencies and modules
find_package(Qt6 REQUIRED COMPONENTS
	Gui
	Widgets
)

# Project target
qt_wrap_cpp(SOURCES_MOC
	"src/image_to_plan_widget.h"
)
qt_add_executable(${PROJECT_NAME}
	${SOURCES_MOC}
	"src/image_to_plan_widget.cpp"
	"src/main.cpp"
)

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt::Gui
		Qt::Widgets
)
