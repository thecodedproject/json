set(target_SRC
    conversion_helpers/lexer.cpp
    builder.cpp
    conversion.cpp
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

