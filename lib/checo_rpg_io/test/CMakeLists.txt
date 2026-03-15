cmake_minimum_required(VERSION 3.27)

project("checo_rpg_io_tests")
enable_testing()

# Find dependencies
find_package(GTest REQUIRED)

# Include modules
include(GoogleTest)

# Project targets
add_executable(${PROJECT_NAME}
	"src/ability_io_tests.cpp"
	"src/currency_io_tests.cpp"
	"src/entity_io_tests.cpp"
	"src/item_io_tests.cpp"
	"src/stat_io_tests.cpp"
	"src/status_effect_io_tests.cpp"
)

# Link dependencies
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		checo::rpg::io
		checo::rpg::test_support
		GTest::gtest_main
)

# Register tests
gtest_discover_tests(${PROJECT_NAME})
