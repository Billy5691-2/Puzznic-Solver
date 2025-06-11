#include "../include/Game/game.hpp"
#include "../include/GUI/window.hpp"
std::string filename = "../levels/level_1_1_cpp.csv";

inline void init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

inline void close() {
    SDL_Quit();
    IMG_Quit();
}

int main(){
    Puzznic::Game Game(filename);
    
    init();
    board board_data = Game.get_board();
    int board_size = board_data.size;
    GUI::Window GUI("Puzznic", board_size);

    while (GUI.isRunning()){
        GUI.pollEvent();
        board_data = Game.get_board();
        GUI.update();
        GUI.render();
    }

    close();
    return 0;
}


