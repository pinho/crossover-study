cmake_minimum_required(VERSION 3.5)

project(CrossoverResearch VERSION 0.9.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Compile libraries
add_subdirectory(include)
add_subdirectory(test)

# Add/Compile sources to binaries
add_subdirectory(src)

# Install binaries on project root directory
install(TARGETS ga4scp DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS ga4maxclique DESTINATION ${CMAKE_INSTALL_PREFIX})
