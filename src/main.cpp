#include "../include/game.hpp"
#include "../include/window.hpp"
std::string filename = "../levels/level_1_1_cpp.csv";

inline void init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
}

inline void close() {
    SDL_Quit();
    IMG_Quit();
}

int main(){
    Puzznic::Game Game(filename);
    init();
    board board_data = Game.get_board();
    position board_size;
    board_size.x = board_data.width;
    board_size.y = board_data.height;
    GUI::Window GUI("Puzznic", board_size);

    while (GUI.isRunning()){
        GUI.pollEvent();
        GUI.update();
        GUI.render();
    }

    close();
    return 0;
}


