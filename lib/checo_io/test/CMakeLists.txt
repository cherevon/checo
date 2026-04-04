cmake_minimum_required(VERSION 3.27)

project("checo_io_tests")
enable_testing()

# Project options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(GTest REQUIRED)

# Include modules
include(GoogleTest)

# Project targets
add_executable(${PROJECT_NAME}
	"src/fundamental_io_tests.cpp"
	"src/map_io_tests.cpp"
	"src/sequence_container_io_tests.cpp"
	"src/set_io_tests.cpp"
	"src/string_io_tests.cpp"
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::io
		GTest::gtest_main
)

# Register tests
gtest_discover_tests(${PROJECT_NAME})
