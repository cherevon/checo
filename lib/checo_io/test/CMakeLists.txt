cmake_minimum_required(VERSION 3.27)

project("checo_io_tests")
enable_testing()

# Find dependencies
find_package(GTest REQUIRED)

# Include modules
include(GoogleTest)

# Project targets
add_executable(${PROJECT_NAME}
	"src/fundamental_io_tests.cpp"
	"src/push_back_container_io_tests.cpp"
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::io
		GTest::gtest_main
)

# Register tests
gtest_discover_tests(${PROJECT_NAME})
