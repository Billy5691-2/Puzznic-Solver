set(Sources
    board_background.cc
    board_buttons.cc
    board.cc
    buttons.cc
    controls.cc
    game_window.cc
    gui_data.cc
    item_counter.cc
    rectangle.cc
    text.cc
    texture_manager.cc
    tile_highlight.cc
    tile_manager.cc)

add_library(${PROJECT_NAME}_gui ${Sources})

# add_compile_options(-Wall -Wextra -Wpedantic)
# add_compile_options(-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)

# "-lSDL2", "-lSDL2_image", "-lSDL2_mixer", "-lSDL2_ttf",

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# find_package(SDL2 REQUIRED)
# find_package(SDL2_ttf REQUIRED)
# find_package(SDL2_imag REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} PRIVATE  ${PROJECT_SOURCE_DIR}/src/common/) # SDL2::SDL2 SDL2::SDL2_ttf SDL2::SDL2_imag

# target_link_libraries(${PROJECT_NAME}_gui ${SDL2_LIBRARIES})



target_include_directories(${PROJECT_NAME}_gui PRIVATE
    include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}_gui PRIVATE
    ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

