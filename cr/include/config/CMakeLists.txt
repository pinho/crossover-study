# ccr/include/config --> libccrconfig.a
cmake_minimum_required(VERSION 3.15)

find_library(YAML_CPP yaml-cpp)

add_library(ccrconfig configuration.cpp)
target_compile_options(ccrconfig PUBLIC -Wall -Werror)
target_link_libraries(ccrconfig yaml-cpp)