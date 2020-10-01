cmake_minimum_required(VERSION 3.5)
project(CrossoverStudy LANGUAGES CXX)
  
## Usando padrão C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} project_lower_name)

# Bibliotecas construídas localmente
add_subdirectory(include/core)

add_executable(run src/run.cxx)
install(TARGETS run DESTINATION ${CMAKE_INSTALL_BINARYDIR})

# O diretório "src" possui subprojetos, um para cada problema de
# otimização abordado no estudo
add_subdirectory(src)

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
  
  # Alvo personalizado para construir a imagem
  add_custom_target(image
    COMMAND ${DOCKER_EXECUTABLE} build --rm -t ${project_lower_name} ${DOCKERFILE_PATH}
    COMMENT "Construindo Imagem Docker: \"${project_lower_name}\""
    VERBATIM) 
  
  # Alvo personalizado para construir o volume
  add_custom_target(volume
    COMMAND ${DOCKER_EXECUTABLE} volume create studyvol
    COMMENT "Construindo Volume Docker: studyvol"
    VERBATIM
  )
endif()
