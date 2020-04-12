# ccr/ --> garun
cmake_minimum_required(VERSION 3.15)
project(CCR VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

add_subdirectory(include/ccr/io)
add_subdirectory(include/ccr/config)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

# Executável principal que roda o algoritmo genético
add_executable(garun src/main.cpp)

target_compile_options(garun PUBLIC -Wall -Werror -Wextra)
target_include_directories(garun PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(garun ccrio ccrconfig)
