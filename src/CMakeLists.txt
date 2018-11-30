set(target_SRC
    conversion_helpers/grammer.cpp
    conversion_helpers/lexer.cpp
    conversion_helpers/to_json_text.cpp
    conversion_helpers/token.cpp
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

