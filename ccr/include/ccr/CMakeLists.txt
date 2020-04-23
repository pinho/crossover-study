cmake_minimum_required(VERSION 3.15)
# CCR internal libraries

# Search by paradiseo libraries
find_library(ParadisEO-EO /usr/local/lib64/libeo.a)
find_library(ParadisEO-Utils /usr/local/lib64/libeoutils.a)

if (ParadisEO-EO OR ParadisEO-Utils)
    message(FATAL_ERROR "ParadisEO not found")
endif()

set(PARADISEOLIBS /usr/local/lib64/libeo.a /usr/local/lib64/libeoutils.a)

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
target_link_libraries(ga ${PARADISEOLIBS})
target_compile_options(config PUBLIC -Wall -Werror)
target_compile_options(ga PUBLIC -Wall -Werror)

# Installation rules
install(TARGETS config ga io
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# if install headers is enable
if (INSTALL_HEADERS)
    install(FILES ${CONFIG_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ccr/config)
    install(FILES ${GA_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ccr/ga)
    install(FILES ${IO_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ccr/io)
endif()