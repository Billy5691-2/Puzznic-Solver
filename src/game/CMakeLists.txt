set(Sources
  game.cc)

add_library(${PROJECT_NAME}_game ${Sources})

include_directories(${PROJECT_SOURCE_DIR}/src/common/)

