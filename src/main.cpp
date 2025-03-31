#include "../include/game.hpp"
#include "../include/gui.hpp"
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
    Game initial_game(filename);
    init();
    Gui base_gui("Puzznic");

    while (base_gui.isRunning()){
        base_gui.pollEvent();
        base_gui.update();
        base_gui.render();
    }

    close();
    return 0;
}


