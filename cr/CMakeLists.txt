cmake_minimum_required(VERSION 3.15)

project(ComparisonRunner VERSION 0.1.0)
set(CXX_STANDARD 17)

add_executable(cr)
target_include_directories(cr PRIVATE ${CMAKE_SOURCE_DIR}/include)
install_targets(cr)