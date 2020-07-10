cmake_minimum_required(VERSION 3.5)

project(CrossoverStudy
  VERSION 1.3.0
  LANGUAGES CXX)
  
## Usando padrão C++ 17
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} project_lower_name)

# Bibliotecas construídas localmente
add_subdirectory(include/core)

add_executable(run source/run.cxx)
install(TARGETS run DESTINATION ${CMAKE_INSTALL_BINARYDIR})

# Cada problema tem um projeto próprio implementando um executável para cada
# problema abordado na pesquisa
add_subdirectory(source/mc) # clique máximo
# add_subdirectory(sc) # cobertura de conjuntos
# add_subdirectory(st) # Árvore de Steiner
# add_subdirectory(mk) # mochila multidimensional

# Automatizar a construção da imagem docker
find_program(DOCKER_EXECUTABLE
  docker HINTS /usr/bin /usr/local/bin )

if(NOT DOCKER_EXECUTABLE)
  message(WARNING "Docker not found. Image will not built")
else()
  message(STATUS "Docker image build enabled")
  
  set(DOCKERFILE_PATH ${CMAKE_SOURCE_DIR})
  
  add_custom_target(image
  COMMAND ${DOCKER_EXECUTABLE} build -t ${project_lower_name} ${DOCKERFILE_PATH}
  COMMENT "Building Docker image: \"${project_lower_name}\""
  VERBATIM) 
endif()