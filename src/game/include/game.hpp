#ifndef C6A9CF15_6A14_43F5_8974_823768ACEA79
#define C6A9CF15_6A14_43F5_8974_823768ACEA79
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <algorithm>
#include <memory>

#include "../../common/constants.hpp"
#include "../../common/enums.hpp"
#include "../../common/structs.hpp"
// #include "boardState.hpp"

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
        // std::shared_ptr<BoardState> activeBoard_;

        std::array<int, NUMBER_OF_ITEMS> itemsCount_;
        std::map<int, Item> items_;
        std::map<int, Platform> platforms_;
        std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE> walls_;
        std::vector<Coord> availableMoves_;
        std::array<std::array<GameTile_t, BOARD_SIZE>, BOARD_SIZE> board_;
        PlayState_t playState_ = PLAYING;

        int timeUnits = 0;

        // static std::unordered_set<BoardState*>

        // void UpdatePlatforms();
        // void UpdateMatches();
        // void SingleTurn();

        // void UpdateGameState();


        public:
        // Game() : Game("../levels/level_1_1_cpp.csv") {}
        explicit Game(const std::string& level);
        // Game(BoardState new_board_state);
        // ~Game();
        // board copy_board();

        // void MakeMove(Move move);
        // void MakeMove(std::vector<Move> moves);

        std::unique_ptr<const std::array<int, NUMBER_OF_ITEMS>> GetItemsCountPtr();
        std::unique_ptr<const std::map<int, Item>> GetItemsPtr();
        std::unique_ptr<const std::map<int, Platform>> GetPlatformsPtr();
        std::unique_ptr<const std::array<std::array<WallType, BOARD_SIZE>, BOARD_SIZE>> GetBoardPtr();
        std::unique_ptr<const std::vector<Coord>> GetAvailableMovesPtr();
        PlayState_t GetGameState();
    };
} // namespace Puzznic


#endif /* C6A9CF15_6A14_43F5_8974_823768ACEA79 */
