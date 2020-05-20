cmake_minimum_required(VERSION 3.6)

file(GLOB SCP_SOURCES setcovering/*.cpp)
file(GLOB MCP_SOURCES maxclique/*.cpp)

add_executable(ga4scp ${SCP_SOURCES})
target_include_directories(ga4scp PUBLIC ../include)
target_link_libraries(ga4scp ga io db)

add_executable(ga4maxclique ${MCP_SOURCES})
target_include_directories(ga4maxclique PUBLIC ../include)
target_link_libraries(ga4maxclique ga io db)
