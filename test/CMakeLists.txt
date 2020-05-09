cmake_minimum_required(VERSION 3.5)
enable_testing()

add_executable(unittests 
        test_crossover_fabric.cpp test_utils.cpp test_cli_instance.cpp)

target_link_libraries(unittests ga io)
target_include_directories(unittests PUBLIC ../include)

add_test(unit COMMAND unittests)
