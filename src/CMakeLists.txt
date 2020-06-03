cmake_minimum_required(VERSION 3.6)

# Nome do executavel a ser gerado é o nome do parojeto em lowercase
string(TOLOWER ${PROJECT_NAME} main_target )
message(STATUS "Main executable: " ${main_target})

file(GLOB SCP_SOURCES scp/*.cpp)
file(GLOB MCP_SOURCES mcp/*.cpp)
file(GLOB MKP_SOURCES mkp/*.cpp)
# file(GLOB STP_SOURCES stp/*.cpp)

include_directories(../include)

add_library(problems STATIC ${SCP_SOURCES} ${MCP_SOURCES} ${MKP_SOURCES})
target_link_libraries(problems io ga db)

add_executable(gastart main.cpp problem_fabric.cpp)
target_link_libraries(gastart problems)

# add_executable(ga4scp ${SCP_SOURCES})
# target_link_libraries(ga4scp ga io db)

# add_executable(ga4maxclique ${MCP_SOURCES})
# target_link_libraries(ga4maxclique ga io db)

# add_executable(ga4multiknap ${MKP_SOURCES})
# target_link_libraries(ga4multiknap ga io db)

install(TARGETS gastart problems
        RUNTIME
          DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY
          DESTINATION ${CMAKE_INSTALL_LIBDIR})
