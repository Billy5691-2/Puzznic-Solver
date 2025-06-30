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
    std::array<int, COLOURS> item_count = Game.get_item_count();
    std::map<position, int> item_list = Game.get_item_list();
    std::vector<platform> platform_list = Game.get_platform_list();
    GUI::Window GUI("Puzznic", board_data);

    while (GUI.isRunning()){
        GUI.pollEvent();
        board_data = Game.get_board();
        GUI.update();
        GUI.render_start();
        GUI.render_board();
        GUI.render_platforms(platform_list);
        GUI.render_items(item_list);
        GUI.render_finish();
    }

    close();
    return 0;
}


