project(css_parser)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)


set(CATCH_BUILD_STATIC_LIBRARY ON CACHE BOOL "" FORCE)
add_subdirectory(extern/catch2)
add_subdirectory(extern/fmt)

add_library(imcss STATIC
    "source/css/model/color.cpp"

    "source/css/tokenizer/tokenize.cpp"
    "source/css/tokenizer/token_type.cpp"
    "source/css/tokenizer/token_stream.cpp"
    
    "source/css/parser/parser_rule_set.cpp"
    "source/css/parser/parser_selector.cpp"
    "source/css/parser/parser_length.cpp"

)

target_include_directories(imcss PUBLIC source)
target_link_libraries(imcss PUBLIC fmt-header-only)
add_subdirectory(tests)
