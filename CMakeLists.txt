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

add_executable(run src/run.cxx)
install(TARGETS run DESTINATION ${CMAKE_INSTALL_BINARYDIR})

# Cada problema tem um projeto próprio implementando um executável para cada
# problema abordado na pesquisa
add_subdirectory(src/mc) # clique máximo
add_subdirectory(src/mk) # mochila multidimensional
add_subdirectory(src/st) # Árvore de Steiner
add_subdirectory(src/sc) # cobertura de conjuntos

# Automatizar a construção da imagem docker
find_program(DOCKER_EXECUTABLE
  docker HINTS /usr/bin /usr/local/bin )

# Verifica se o docker está instalado
# Se sim: alvos para a imagem e para o volume serão criados
if(NOT DOCKER_EXECUTABLE)
  message(WARNING "Docker not found. Image and Volume will not built")
else()
  message(STATUS "Targets for Docker image and volume is enabled")
  set(DOCKERFILE_PATH ${CMAKE_SOURCE_DIR})
  
  add_custom_target(image
    COMMAND ${DOCKER_EXECUTABLE} build --rm -t ${project_lower_name} ${DOCKERFILE_PATH}
    COMMENT "Construindo Imagem Docker: \"${project_lower_name}\""
    VERBATIM) 
  
  add_custom_target(volume
    COMMAND ${DOCKER_EXECUTABLE} volume create studyvol
    COMMENT "Construindo Volume Docker: studyvol"
    VERBATIM
  )
endif()
