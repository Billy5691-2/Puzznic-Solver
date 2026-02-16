#ifndef C6A9CF15_6A14_43F5_8974_823768ACEA79
#define C6A9CF15_6A14_43F5_8974_823768ACEA79
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "../../common/constants.hpp"
#include "../../common/enums.hpp"
#include "../../common/structs.hpp"

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

Player move + gravity can happen in the same time
May disallow this to ensure A* algorithm can work 100% of the time
Future idea - Make each math increase time units by 1 per block destroyed. It may make A* optimal

*/

#define USE_SEEN_BOARDS   true
#define PRESENT_ALL_MOVES true // Whether to present moves that have no immediate strategic value
#define DETECT_LEDGES     true // At board init, detect ledges to find strategic positions - requires presentAllMoves = fal
#define MULTI_THREAD      false // Multithread move search

namespace Puzznic {

    constexpr Coord_t LEFT_POS = {0, -1};
    constexpr Coord_t RIGHT_POS = {0, 1};
    constexpr Coord_t UP_POS = {1, 0};
    constexpr Coord_t DOWN_POS = {-1, 0};
    constexpr std::array<Coord_t, 4> ALL_DIRECTIONS = {LEFT_POS, RIGHT_POS, UP_POS, DOWN_POS};

    struct ItemMove_t {
        int itemId = -1;
        Coord_t finalPosition;
    };

    using MoveChain_u = std::vector<Coord_t>;
    using AllMoves_u = std::vector<std::map<Coord_t, MoveChain_u>>;

    class Game {
        Board_t board_;

        std::array<int, NUMBER_OF_ITEMS> itemsCount_ = {}; // This should just be in board_t
        PlayState_t playState_ = PLAYING;
        std::shared_ptr<AllMoves_u> availableMoves_ = nullptr;
        static std::unordered_set<Board_t> SeenBoards;
        bool efficientSolverMode_ = true; // Use SeenBoards to avoid exploring previously seen boards

        // Boards actions
        void UpdateHorizontalPlatforms();
        void UpdateVerticalPlatforms();
        void UpdateGravity();
        void UpdateMatches(); // Destroyed items should be moved off the board
        void UpdateGameState();

        // Player actions
        void MoveLeft(int itemId);
        void MoveRight(int itemId);
        void Wait();

        bool IsTileEmpty(const Coord_t& pos);
        bool IsAdjacent(const Coord_t& posOne, const Coord_t& posTwo);
        void CountItems();

        void MakeMove(const Move_t&);
        void FindValidMoves();

        public:
        explicit Game(const std::string& level); // Init a level
        Game(const Board_t& board, const Move_t& move,
             const std::shared_ptr<AllMoves_u>& moveMap);                // Search for available moves
        Game(const Board_t& board, const std::vector<Move_t>& moveList); // Solver search object

        void MakeMoveChain(const std::vector<Move_t>& moveList);

        const std::array<int, NUMBER_OF_ITEMS>& GetItemsCount();
        const std::vector<Coord_t> GetAvailableMoves(const std::size_t itemIndex);
        PlayState_t GetGameState();

        const Board_t& GetBoard();
    };
} // namespace Puzznic


#endif /* C6A9CF15_6A14_43F5_8974_823768ACEA79 */
