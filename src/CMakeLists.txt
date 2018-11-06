set(target_SRC
    tree.cpp
    value.cpp
)

add_library(json
    ${target_SRC}
)

target_include_directories(
    json PUBLIC
    ${json_SOURCE_DIR}/include
)

