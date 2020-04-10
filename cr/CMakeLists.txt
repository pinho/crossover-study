# ccr/ --> garun
cmake_minimum_required(VERSION 3.15)
project(CrossoverComparisonRunner VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

add_subdirectory(include/io)
add_subdirectory(include/config)
add_subdirectory(test)

# Executável principal que roda o algoritmo genético
add_executable(garun main.cpp)
target_include_directories(garun PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(garun ccrconfig)