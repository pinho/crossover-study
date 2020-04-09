cmake_minimum_required(VERSION 3.15)
project(ComparisonRunner VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

add_subdirectory(include/io)

install(TARGETS cr-io
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)