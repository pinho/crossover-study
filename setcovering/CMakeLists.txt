cmake_minimum_required(VERSION 3.5)

add_executable(ga-setcovering main.cpp set_covering_problem.cpp)
target_include_directories(ga-setcovering PUBLIC ../include)
target_link_libraries(ga-setcovering config ga io)
target_compile_options(ga-setcovering PUBLIC -Wall -Werror)

install(TARGETS ga-setcovering DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
