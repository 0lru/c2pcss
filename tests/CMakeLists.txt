add_executable(imcss_tests 
    "source/test_lexer.cpp"
 )
target_link_libraries(imcss_tests  PRIVATE imcss Catch2 Catch2::Catch2WithMain)

add_custom_command(
     TARGET imcss_tests 
     COMMENT "run imcss tests"
     POST_BUILD 
     COMMAND imcss_tests
)
