cmake_minimum_required(VERSION 3.15)

add_executable(ccr-tests
        test_configuration.cpp)
target_include_directories(ccr-tests PUBLIC ../include)
target_link_libraries(ccr-tests ccrio ccrconfig)

add_test(ccrtest ccr-tests -s)
