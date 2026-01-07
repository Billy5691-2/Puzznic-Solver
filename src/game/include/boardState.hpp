// #ifndef CFA7B4D0_3135_437F_984A_C68B15DD75BB
// #define CFA7B4D0_3135_437F_984A_C68B15DD75BB
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <stdlib.h>
// #include <vector>
// #include <string>
// #include <map>
// //#include <unordered_map>
// #include <unordered_set>
// #include "src/global/structs.hpp"
// #include "src/global/constants.hpp"

// /*
// Items: ##
// 1 = red
// 2 = blue
// 3 = green
// 4 = pink
// 5 = purple
// 6 = cyan
// 7 = brown
// 8 = orange
// 9 = yellow

// */

// namespace Puzznic{
//     class BoardState {
//         int boardSize_;
//         BoardArr gameBoard_;
//         std::array<int, COLOURS> itemCountArr_;
//         std::map<Coord_t, int> itemMap_;
//         std::vector<Platform_t> y_PlatformVec;
//         std::vector<Platform_t> x_PlatformVec;
//         std::vector<Move> movesToHere_;
//         bool gameWon_ = false;
//         bool gameLost_ = false;

//         bool GameLoop(Move move);
//         void UpdateY_Platforms();
//         void UpdateX_Platforms();
//         void UpdateItems();
//         void MatchItems();
//         bool GameFinished();

//         void print_board() const;
//         void print_item_list() const;

//         bool MoveTile(Coord_t oldCoord, Coord_t newCoord);
//         bool MoveItem(Coord_t oldCoord, Coord_t newCoord);
//         void UpdateItemCount(int colour);

//         void SetBoardCoord(const Coord_t coord, Tile tile);

//         public:
//             BoardState() : BoardState("../levels/level_1_1_cpp.csv"){}
//             BoardState(std::string level);
//             BoardState(BoardArr temp_game_board, std::array<int, COLOURS> temp_item_count,
//                 std::map<Coord_t, int> temp_item_list,
//                 std::vector<Platform_t> temp_hor_list, std::vector<Platform_t> temp_vert_list) :
//                 gameBoard_(temp_game_board),
//                 itemCountArr_(temp_item_count), itemMap_(temp_item_list),
//                 y_PlatformVec(temp_hor_list), x_PlatformVec(x_PlatformVec) {}
//             ~BoardState();
//             BoardState copy();

//             void MakeMove(const Move& move);
//             void MakeMove(const std::vector<Move>&);

//             const std::vector<Platform_t>& GetPlatformVecs();
//             const int GetBoardSize() const { return boardSize_; }
//             const Tile& GetBoardPos(Coord_t pos) const { return gameBoard_[pos.x][pos.y]; }
//             const std::array<int, COLOURS>& GetItemCount() const { return itemCountArr_; }
//             const BoardArr& GetBoard() const { return gameBoard_; }
//             const std::map<Coord_t, int>& GetItemMap() const { return itemMap_; }
//             const bool GetWinState() { return gameWon_; }
//             const bool GetLoseState() { return gameLost_; }
//             const std::vector<Move>& MoveVec() { return movesToHere_; }


//     };
// }


// #endif /* CFA7B4D0_3135_437F_984A_C68B15DD75BB */
