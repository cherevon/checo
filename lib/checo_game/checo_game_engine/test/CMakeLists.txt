cmake_minimum_required(VERSION 3.27)

project("checo_game_engine_tests" LANGUAGES CXX)
enable_testing()

# Dependencies and modules
find_package(GTest REQUIRED)
include(GoogleTest)

# Project target
add_executable(${PROJECT_NAME}
	"src/tag_component_tests.cpp"
)

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::game::engine
		GTest::gtest_main
)

# Register tests
gtest_discover_tests(${PROJECT_NAME})