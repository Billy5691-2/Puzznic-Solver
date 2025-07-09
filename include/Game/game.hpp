#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>

#include <memory>
#include <algorithm>

#include "../structs.hpp"
#include "../constants.hpp"
#include "boardState.hpp"

/*
Items: ##
1 = red
2 = blue
3 = green
4 = pink
5 = purple
6 = cyan
7 = brown
8 = orange
9 = yellow

*/

namespace Puzznic {
    class Game {
        BoardState* activeBoard_;
        std::vector<move> movesToHere_;

        //static std::unordered_set<BoardState*>

        bool gameWon_ = false;
        bool gameLost_ = false;

        void game_state();

        public:
            Game() : Game("../levels/level_1_1_cpp.csv") {}
            Game(std::string level);
            Game(BoardState new_board_state);
            ~Game();
            //board copy_board();

            /*
            bool get_win_state();
            bool get_lose_state();

            std::array<int, COLOURS> GetItemCount();
            board GetBoard();
            std::map<position, int> GetItemMap();
            std::vector<platform> GetPlatformVecs();

            */
            void MakeMove(move move);
            void MakeMove(std::vector<move> moves);

            board Game::GetBoard(){ return activeBoard_->GetBoard(); }
            std::array<int, COLOURS> Game::GetItemCount(){ return activeBoard_->GetItemCount(); }
            std::map<position, int> Game::getItemList() { return activeBoard_->GetItemMap(); }
            std::vector<platform> Game::GetPlatformList() { return activeBoard_->GetPlatformVecs(); }

            bool Game::GetWinState(){ return gameLost_; }
            bool Game::GetLoseState(){ return gameWon_; }

    };
}