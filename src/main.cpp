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

    position temp_move;
    temp_move.x = 3;
    temp_move.y = 3;
    std::vector<position> move_list;
    move_list.push_back(temp_move);

    GUI::Window GUI("Puzznic", board_data, platform_list);

    while (GUI.isRunning()){
        GUI.pollEvent();
        board_data = Game.get_board();
        if (GUI.update()) {
            if (GUI.change_level_state()){
                std::string lvl_file = GUI.new_level_file();
                std::cout << "New Level: " << lvl_file << "\n"; 
            }
            if (GUI.start_solver_state()){
                std::cout << "Start solver\n";
            }
            if (GUI.get_highlight_change()){
                move potential_move = GUI.get_move();
                std::cout << "Move Recieved\n";
            }
        }

        item_count = Game.get_item_count();
        platform_list = Game.get_platform_list();
        item_list = Game.get_item_list();
        GUI.render(item_list, platform_list, item_count, move_list);

    }

    close();
    return 0;
}


