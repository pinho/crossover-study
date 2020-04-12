cmake_minimum_required(VERSION 3.15)

add_executable(ccr-tests
        test_configuration.cpp)
target_include_directories(ccr-tests PUBLIC ../include)
target_link_libraries(ccr-tests ccrio ccrconfig)

install(TARGETS ccr-tests DESTINATION ${CMAKE_SOURCE_DIR}/test)

add_test(NAME ccrtest COMMAND ccr-tests -s)
