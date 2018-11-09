
set(target_SRC
    test_builder.cpp
    test_tree_array_usage.cpp
    test_tree_construction.cpp
    test_tree_document_usage.cpp
    test_tree_erase.cpp
    test_tree_iteration.cpp
    test_tree_value_usage.cpp
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
