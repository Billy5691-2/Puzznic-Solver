cmake_minimum_required(VERSION 3.16.3)
project(PuzznicSolver VERSION 1.0
                      DESCRIPTION "A reimplementation of Puzznic with an A* based solver"
                      LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CSS_EXTENSIONS OFF)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 4)
set(CMAKE_BINARY_DIR /home/billy5691/CPP_Projects/Puzznic-Solver/bin)
set(CMAKE_SOURCE_DIR /home/billy5691/CPP_Projects/Puzznic-Solver/)
set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -pthread -Werror -Wall")

add_subdirectory(src)


