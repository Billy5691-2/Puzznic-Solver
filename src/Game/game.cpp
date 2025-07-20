#include "../../include/Game/game.hpp"

/*
Requirements:

Generate list of valid moves for an item
Generate list of all valid moves

Check generated list of moves against hash to reduce compute

Check order of operations:
Gravity vs destruction
items on platforms vs destruction



*/


/*
namespace Puzznic {
    Game::Game(std::string level) {
        activeBoard_ = std::make_shared<BoardState>(level);
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
        std::copy(&game_board.board[0][0], &game_board.board[0][0]+kBoardSize*kBoardSize, &new_board.board[0][0]);
        return new_board;
    }
}
*/