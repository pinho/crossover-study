cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 17)

add_executable(ga-setcov setcov_main.cpp set_covering_problem.cpp)
target_include_directories(ga-setcov PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ga-setcov config ga io)
