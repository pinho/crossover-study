cmake_minimum_required(VERSION 3.5)
enable_testing()

add_executable(ccr-tests
        test_configuration.cpp test_crossover_fabric.cpp test_utils.cpp)

target_include_directories(ccr-tests PUBLIC ../include)
target_link_libraries(ccr-tests config ga io)

install(TARGETS ccr-tests DESTINATION ${CMAKE_SOURCE_DIR}/test)

add_test(NAME ccrtest COMMAND ccr-tests)
