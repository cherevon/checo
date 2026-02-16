cmake_minimum_required (VERSION 3.23)

project("minecraft_auto_sell")

# Project target
add_executable(${PROJECT_NAME} "main.cpp")

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE checo::logging)

# Copy all dependent DLLs next to the executable after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS
)
