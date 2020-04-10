cmake_minimum_required(VERSION 3.15)
enable_testing()

add_executable(cr-tests
        test_io.cpp)
target_include_directories(cr-tests PUBLIC ../include)
target_link_libraries(cr-tests cr-io)

add_test(NAME crtest COMMAND cr-tests)