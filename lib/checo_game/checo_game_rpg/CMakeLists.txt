cmake_minimum_required(VERSION 3.27)

project("checo_game_rpg" LANGUAGES CXX)

# Project target
add_library(${PROJECT_NAME} STATIC
    "src/ability_component.cpp"
    "src/status_effect_component.cpp"
)
add_library(checo::game::rpg ALIAS ${PROJECT_NAME})

# Target compile settings
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Target includes
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC checo::game::engine)
