cmake_minimum_required(VERSION 3.27)

project("checo_io_tests" LANGUAGES CXX)
enable_testing()

# Dependencies and modules
find_package(GTest REQUIRED)
include(GoogleTest)

# Project target
add_executable(${PROJECT_NAME}
	"src/fundamental_io_tests.cpp"
	"src/map_io_tests.cpp"
	"src/sequence_container_io_tests.cpp"
	"src/set_io_tests.cpp"
	"src/string_io_tests.cpp"
)

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::io
		GTest::gtest_main
)

# Register tests
gtest_discover_tests(${PROJECT_NAME})
