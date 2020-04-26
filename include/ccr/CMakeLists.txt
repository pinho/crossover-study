cmake_minimum_required(VERSION 3.8)
# CCR internal libraries

# Search by paradiseo libraries
find_library(PEO_LIB NAMES eo libeo)
find_library(PEOU_LIB NAMES eoutils libeoutils)

if (NOT PEO_LIB OR NOT PEOU_LIB)
    message(${PEO_LIB})
endif()

# Header files groups
file(GLOB CONFIG_HEADERS config/*.h)
file(GLOB GA_HEADERS ga/*.h)
file(GLOB IO_HEADERS io/*.h)

# Source files groups
file(GLOB CONFIG_SOURCES config/*.cpp)
file(GLOB GA_SOURCES ga/*.cpp)
file(GLOB IO_SOURCES io/*.cpp)

# Libraries
add_library(config ${CONFIG_SOURCES})
add_library(ga ${GA_SOURCES})
add_library(io ${IO_SOURCES})
target_link_libraries(config yaml-cpp)
target_link_libraries(ga eo eoutils)
target_compile_options(config PUBLIC -Wall -Werror -Wextra)
target_compile_options(ga PUBLIC -Wall -Werror -Wextra)

# Installation rules
install(TARGETS config ga io
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# if install headers is enable
if (INSTALL_HEADERS)
    install(FILES ${CONFIG_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ccr/config)
    install(FILES ${GA_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ccr/ga)
    install(FILES ${IO_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ccr/io)
endif()