#include <iostream>
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

/*
Requirements:

Generate list of valid moves for an item
Generate list of all valid moves

Check generated list of moves against hash to reduce compute

Check order of operations:
Gravity vs destruction
items on platforms vs destruction



*/

namespace Puzznic {
    class Game {
        std::shared_ptr<BoardState> activeBoard_;

        //static std::unordered_set<BoardState*>

        public:
            Game() : Game("../levels/level_1_1_cpp.csv") {}
            Game(std::string level);
            Game(BoardState new_board_state);
            ~Game();
            //board copy_board();

            void MakeMove(Move move);
            void MakeMove(std::vector<Move> moves);

            const BoardArr& GetBoard() const { return activeBoard_->GetBoard(); }
            const std::array<int, COLOURS>& GetItemCount() const { return activeBoard_->GetItemCount(); }
            const std::map<Coord, int>& getItemList() const { return activeBoard_->GetItemMap(); }
            const std::vector<Platform>& GetPlatformList() const { return activeBoard_->GetPlatformVecs(); }
            const int GetBoardSize() const { return activeBoard_->GetBoardSize(); }

            const bool GetWinState() const { return activeBoard_->GetWinState(); }
            const bool GetLoseState() const { return activeBoard_->GetLoseState(); }

    };
}