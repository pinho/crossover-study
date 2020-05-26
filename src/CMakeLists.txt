cmake_minimum_required(VERSION 3.6)

file(GLOB SCP_SOURCES scp/*.cpp)
file(GLOB MCP_SOURCES mcp/*.cpp)
file(GLOB MKP_SOURCES mkp/*.cpp)
# file(GLOB STP_SOURCES stp/*.cpp)

include_directories(../include)

add_library(problems STATIC ${SCP_SOURCES} ${MCP_SOURCES} ${MKP_SOURCES})
target_link_libraries(problems io ga db)

add_executable(gastart main.cpp)
target_link_libraries(gastart problems)

# add_executable(ga4scp ${SCP_SOURCES})
# target_link_libraries(ga4scp ga io db)

# add_executable(ga4maxclique ${MCP_SOURCES})
# target_link_libraries(ga4maxclique ga io db)

# add_executable(ga4multiknap ${MKP_SOURCES})
# target_link_libraries(ga4multiknap ga io db)
