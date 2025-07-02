#include "../../include/Game/game.hpp"
namespace Puzznic {
    Game::Game(std::string level) {
        BoardState active_board(level);
        //active_board(level);
    }

    Game::Game(BoardState new_board_state) {
        std::cout << "TBD\n";
    }

    //Game Destructor
    Game::~Game() {
        std::cout << "Close Game 2\n";
    }

    

    /*board Game::copy_board(){
        std::cout << "TBD\n";
        
        board new_board;
        new_board.size = game_board.size;
        //new_board.height = game_board.height;
        //new_board.width = game_board.width;
        std::copy(&game_board.board[0][0], &game_board.board[0][0]+BOARD_SIZE*BOARD_SIZE, &new_board.board[0][0]);
        return new_board;
    }*/

    board Game::get_board(){ return active_board.get_board(); }
    std::array<int, COLOURS> Game::get_item_count(){ return active_board.get_item_count(); }
    std::map<position, int> Game::get_item_list() { return active_board.get_item_list(); }
    std::vector<platform> Game::get_platform_list() { return active_board.get_platform_list(); }

}