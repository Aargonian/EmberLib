set(DEMO_SOURCES demo.c)

add_executable(demo EXCLUDE_FROM_ALL ${DEMO_SOURCES})
target_link_libraries(demo PRIVATE EmberLib)
target_include_directories(demo PRIVATE ${EmberLib_INCLUDE_DIRS})

add_custom_command(
        TARGET demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Test.txt ${CMAKE_CURRENT_BINARY_DIR}/Test.txt
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Test.txt
)