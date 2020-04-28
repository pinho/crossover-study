cmake_minimum_required(VERSION 3.5)

add_executable(main main.cpp set_covering_problem.cpp)
target_include_directories(main PUBLIC ../include)
target_link_libraries(main config ga)
target_compile_options(main PUBLIC -Wall)
