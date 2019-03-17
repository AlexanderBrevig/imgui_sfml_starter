add_executable(tests tests.cpp)

target_link_libraries(tests src)
 
add_test(tests tests)