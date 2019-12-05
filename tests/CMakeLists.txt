# If pkg-config is not installed on the system, then CHECK_INSTALL_DIR variable
# must be set to the install location of Check
#
# set(CHECK_INSTALL_DIR "C:/Program Files/check")

if(${BUILD_TESTS})
    find_package(Check REQUIRED)

    set(TEST_SOURCES check_arraylist_new.c
            check_util.h
            check_util.c)
    add_executable(emberlib.check EXCLUDE_FROM_ALL ${TEST_SOURCES})

    target_link_directories(emberlib.check PRIVATE ${CHECK_LIBRARY_DIRS})
    target_link_libraries(emberlib.check PRIVATE ${CHECK_LIBRARIES})
    target_link_libraries(emberlib.check PRIVATE EmberLib)
endif(${BUILD_TESTS})
