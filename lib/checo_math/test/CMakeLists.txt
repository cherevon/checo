cmake_minimum_required(VERSION 3.23)

project("TEST_checo_math")
enable_testing()

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(GTest REQUIRED)

# Include modules
include(GoogleTest)

# Source files
add_executable(${PROJECT_NAME}
	"src/matrix/test_matrix_comparison.cpp"
	"src/matrix/test_matrix_constructor.cpp"
	"src/matrix/test_matrix_multiply.cpp"
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		checo::math
		GTest::gtest_main
)

# Discover GoogleTest tests
gtest_discover_tests(${PROJECT_NAME})