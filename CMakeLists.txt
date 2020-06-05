cmake_minimum_required(VERSION 3.5)

project(CrossoverResearch VERSION 0.9.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

# Compile unit tests
if(BUILD_TESTING)
  enable_testing()
  message(STATUS "Build of unit tests enabled")
  add_subdirectory(test)
endif()

# Add/Compile sources to binaries
add_subdirectory(src)
