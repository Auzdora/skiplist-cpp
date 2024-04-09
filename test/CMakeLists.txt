cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

file(GLOB_RECURSE SKIPLIST_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*test.cpp")

# #####################################################################################################################
# MAKE TARGETS
# #####################################################################################################################

# #########################################
# "make XYZ_test"
# #########################################
foreach (skiplist_test_source ${SKIPLIST_TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(skiplist_test_filename ${skiplist_test_source} NAME)
    string(REPLACE ".cpp" "" skiplist_test_name ${skiplist_test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${skiplist_test_name} EXCLUDE_FROM_ALL ${skiplist_test_source})

    gtest_discover_tests(${skiplist_test_name}
            EXTRA_ARGS
            --gtest_output=xml:${CMAKE_BINARY_DIR}/test/${skiplist_test_name}.xml
            --gtest_catch_exceptions=0
            DISCOVERY_TIMEOUT 120
            PROPERTIES
            TIMEOUT 120
            )

    target_link_libraries(${skiplist_test_name} skiplist gtest gmock_main)

    # Set test target properties and dependencies.
    set_target_properties(${skiplist_test_name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
            COMMAND ${skiplist_test_name}
            )
endforeach ()
