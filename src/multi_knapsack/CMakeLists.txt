cmake_minimum_required(VERSION 3.15)
project(MultiKnap)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} main_target)

include_directories(../../include)
add_compile_options("-Wunused")

add_executable(${main_target}
  main.cxx
  mknap_problem.cxx )
target_link_libraries(${main_target} core-ga core-utils vsqlitepp)

install(TARGETS ${main_target} DESTINATION ${CMAKE_INSTALL_BINARYDIR})
