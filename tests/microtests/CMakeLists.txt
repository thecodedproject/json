
set(target_SRC
    test_tree.cpp
    test_value.cpp
)

add_executable(json_microtests
    ${target_SRC}
)

target_link_libraries(json_microtests
    json
    gmock
    gtest_main
)

add_test_to_make_check(json_microtests)
