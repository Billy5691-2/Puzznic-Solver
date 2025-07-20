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
    //std::array<std::array<Tile, 20>, 20> board = Game.GetBoard();
    //int boardSize = Game.GetBoardSize();
    std::array<int, COLOURS> item_count = Game.GetItemCount();
    std::map<Coord, int> item_list = Game.getItemList();
    std::vector<Platform> platform_list = Game.GetPlatformList();
    BoardArr board = Game.GetBoard();
    int boardSize = Game.GetBoardSize();


    Coord temp_move;
    temp_move.x = 3;
    temp_move.y = 3;
    std::vector<Coord> move_list;
    move_list.push_back(temp_move);

    GUI::Window GUI("Puzznic", board, platform_list, boardSize);

    while (GUI.IsRunning()){
        GUI.PollEvent();
        if (GUI.Update()) {
            if (GUI.ChangeLevelState()){
                std::string lvl_file = GUI.GetLvlFilename();
                std::cout << "New Level: " << lvl_file << "\n"; 
            }
            if (GUI.StartSolverState()){
                std::cout << "Start solver\n";
            }
            if (GUI.GetHightlightChange()){
                Move potential_move = GUI.GetMove();
                std::cout << "Move Recieved\n";
            }
        }

        item_count = Game.GetItemCount();
        platform_list = Game.GetPlatformList();
        item_list = Game.getItemList();
        GUI.Render(item_list, platform_list, item_count, move_list);

    }

    close();
    return 0;
}


