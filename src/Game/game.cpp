#include "../../include/Game/game.hpp"
namespace Puzznic {
    Game::Game(std::string level) {
        BoardState active_board(level);
    }

    //Game Destructor
    Game::~Game() {
        std::cout << "Close Game 2\n";
    }

    board Game::get_board(){
        return active_board.get_board();
    }

    std::array<int, COLOURS> Game::get_item_count(){
        return active_board.get_item_count();
    }

    board Game::copy_board(){
        /*
        board new_board;
        new_board.size = game_board.size;
        //new_board.height = game_board.height;
        //new_board.width = game_board.width;
        std::copy(&game_board.board[0][0], &game_board.board[0][0]+BOARD_SIZE*BOARD_SIZE, &new_board.board[0][0]);
        return new_board;*/
    }

}