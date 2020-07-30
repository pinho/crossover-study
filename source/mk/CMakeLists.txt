cmake_minimum_required(VERSION 3.15)
project(MultiKnap)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} main_target)

include_directories(../../include)
link_libraries(core-ga core-utils vsqlitepp)

add_executable(${main_target}
  main.cxx
  mknap_problem.cxx )

install(TARGETS ${main_target} DESTINATION ${CMAKE_INSTALL_BINARYDIR})
