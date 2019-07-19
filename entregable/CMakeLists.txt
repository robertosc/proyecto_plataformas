cmake_minimum_required(VERSION 3.0)
project(cajero_automatico)

set(sources
  src/main.c
  src/menu.c
  src/funciones.c
  src/funciones2.c
  src/funciones3.c)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(cajero_automatico ${sources})

install (TARGETS cajero_automatico DESTINATION bin)
