#include "../../include/Game/game.hpp"

/*
Requirements:

Generate list of valid moves for an item
Generate list of all valid moves

Check generated list of moves against hash to reduce compute

Check order of operations:
Gravity vs destruction
items on platforms vs destruction



Implemented:
- Check if game is still winnable or has been won


*/



namespace Puzznic {
    Game::Game(std::string level) {
        active_board = new BoardState(level);
        std::shared_ptr<BoardState> current_board = std::make_shared<BoardState>(level);
    }

    Game::Game(BoardState new_board_state) {
        std::cout << "TBD\n";
    }

    //Game Destructor
    Game::~Game() {
        delete active_board;
        std::cout << "Close Game 2\n";
    }

    void Game::game_state(){
        bool won = true;
        for (const auto& count : active_board->get_item_count()){
            if (count  == 1){
                game_lost = true;
                return;
            }
            if (count > 0){
                won = false;
            }
        }
        game_won = won;
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

    board Game::get_board(){ return active_board->get_board(); }
    std::array<int, COLOURS> Game::get_item_count(){ return active_board->get_item_count(); }
    std::map<position, int> Game::get_item_list() { return active_board->get_item_list(); }
    std::vector<platform> Game::get_platform_list() { return active_board->get_platform_list(); }

    bool Game::get_lose_state(){ return game_lost; }
    bool Game::get_win_state(){ return game_won; }

}