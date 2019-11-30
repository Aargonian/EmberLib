set(DEMO_SOURCES demo.c)

add_executable(demo EXCLUDE_FROM_ALL ${DEMO_SOURCES})
target_link_libraries(demo PRIVATE EmberLib)
target_include_directories(demo PRIVATE ${EmberLib_INCLUDE_DIRS})
