if(${BUILD_TESTS})
    # If pkg-config is not installed on the system, or if you are on Windows, then CHECK_INSTALL_DIR variable must be
    # set to the install location of libcheck.
    #
    # set(CHECK_INSTALL_DIR "C:/Program Files/check")
    find_package(Check REQUIRED)

    set(TEST_HEADERS check_util.h)
    set(TEST_SOURCE check_util.c)

    set(ARRAYLIST_TEST_SOURCES ${TEST_HEADERS} ${TEST_SOURCE}
            check_emberlist.c)

    set(EMBER_STRING_TEST_SOURCES ${TEST_HEADERS} ${TEST_SOURCE}
                                  check_ember_string.c)

    add_executable(test_arraylist ${ARRAYLIST_TEST_SOURCES})
    add_executable(test_ember_string ${EMBER_STRING_TEST_SOURCES})

    target_link_directories(test_arraylist PRIVATE ${CHECK_LIBRARY_DIRS})
    target_link_libraries(test_arraylist PRIVATE ${CHECK_LIBRARIES})
    target_link_libraries(test_arraylist PRIVATE EmberLib)

    target_link_directories(test_ember_string PRIVATE ${CHECK_LIBRARY_DIRS})
    target_link_libraries(test_ember_string PRIVATE ${CHECK_LIBRARIES})
    target_link_libraries(test_ember_string PRIVATE EmberLib)

    enable_testing()
    add_test(NAME test_arraylist COMMAND test_arraylist)
    add_test(NAME test_ember_string COMMAND test_ember_string)

endif(${BUILD_TESTS})
