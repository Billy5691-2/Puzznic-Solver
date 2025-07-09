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
        std::shared_ptr<BoardState> activeBoard_;
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

            void MakeMove(move move);
            void MakeMove(std::vector<move> moves);

            std::array<std::array<tile, 20>, 20> GetBoard(){ return activeBoard_->GetBoard(); }
            std::array<int, COLOURS> GetItemCount(){ return activeBoard_->GetItemCount(); }
            std::map<position, int> getItemList() { return activeBoard_->GetItemMap(); }
            std::vector<platform> GetPlatformList() { return activeBoard_->GetPlatformVecs(); }
            int GetBoardSize() { return activeBoard_->GetBoardSize(); }

            bool GetWinState(){ return gameLost_; }
            bool GetLoseState(){ return gameWon_; }

    };
}