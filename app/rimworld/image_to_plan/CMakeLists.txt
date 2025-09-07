cmake_minimum_required(VERSION 3.27)

project("rimworld_image_to_plan")

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Qt6 REQUIRED COMPONENTS
	Gui
	Widgets
)

# Project targets
qt_wrap_cpp(SOURCES_MOC
	"src/image_to_plan_widget.h"
)
qt_add_executable(${PROJECT_NAME}
	${SOURCES_MOC}
	"src/image_to_plan_widget.cpp"
	"src/main.cpp"
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt::Gui
		Qt::Widgets
)