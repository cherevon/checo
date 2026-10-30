cmake_minimum_required(VERSION 3.27)

project("checo_core_tests" LANGUAGES CXX)
enable_testing()

# Dependencies and modules
find_package(GTest REQUIRED)
include(GoogleTest)

# Project target
add_executable(${PROJECT_NAME}
	"src/byte_array_tests.cpp"
    "src/string_tests.cpp"
    "src/variant_tests.cpp"
    "src/vector_tests.cpp"
)

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::core
		GTest::gtest_main
)

# Register tests
gtest_discover_tests(${PROJECT_NAME})
