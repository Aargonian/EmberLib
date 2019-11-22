# If pkg-config is not installed on the system, then CHECK_INSTALL_DIR variable must be set to the install location of Check
# set(CHECK_INSTALL_DIR "C:/Program Files/check")

find_package(Check REQUIRED)

set(TEST_SOURCES
	check_arraylist_new.c)

add_executable(check_emberlib ${TEST_SOURCES})

target_include_directories(check_emberlib PRIVATE ${CHECK_INCLUDE_DIRS})
target_include_directories(check_emberlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../EmberLib/include)

target_link_directories(check_emberlib PRIVATE ${CHECK_LIBRARY_DIRS})
target_link_libraries(check_emberlib PRIVATE ${CHECK_LIBRARIES})
