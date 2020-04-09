cmake_minimum_required(VERSION 3.15)

add_library(cr-io
        dimacs_reader.cpp)

add_compile_options("-Wall -Werror -Wextra")