
set(target_SRC
    test_read_json_from_file.cpp
    test_template_value.cpp
)

add_executable(json_sandbox_tests
    ${target_SRC}
)

target_link_libraries(json_sandbox_tests
    json
    gmock
    gtest_main
)

add_dependencies(check json_sandbox_tests)
