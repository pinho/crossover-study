cmake_minimum_required(VERSION 3.5)

project(CrossoverResearch VERSION 0.9.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(include)
add_subdirectory(test)

add_subdirectory(setcovering)
