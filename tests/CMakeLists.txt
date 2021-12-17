add_executable(imcss_tests 

    "source/test_tokenize.cpp"
    "source/test_tokenize_comment.cpp"
    "source/test_tokenize_ident.cpp"
    "source/test_tokenize_escape.cpp"
    "source/test_tokenize_quoted_string.cpp"
    "source/test_tokenize_number.cpp"
    "source/test_tokenize_url.cpp"
    "source/test_tokenize_data_integrity.cpp"
    "source/test_tokenize_error.cpp"
    
    "source/test_parse_selector.cpp"
 
 )

target_link_libraries(imcss_tests  PRIVATE imcss Catch2 Catch2::Catch2WithMain)

add_custom_command(
     TARGET imcss_tests 
     COMMENT "run imcss tests"
     POST_BUILD 
     COMMAND imcss_tests
)
