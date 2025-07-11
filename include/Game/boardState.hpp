#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
//#include <unordered_map>
#include <unordered_set>
#include "../structs.hpp"
#include "../constants.hpp"

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

namespace Puzznic{
    class BoardState {
        int boardSize_;
        //board gameBoard_;
        std::array<std::array<tile, 20>, 20> gameBoard_;
        std::array<int, COLOURS> itemCountArr_;
        std::map<position, int> itemMap_;
        std::vector<platform> y_PlatformVec;
        std::vector<platform> x_PlatformVec;
        
        void GameLoop(move move);
        void UpdateY_Platforms();
        void UpdateX_Platforms();
        void UpdateItems();
        void MatchItems();

        void print_board();
        void print_item_list();

        bool MoveTile(position oldCoord, position newCoord);
        bool MoveItem(position oldCoord, position newCoord);
        void UpdateItemCount(int colour);

        void SetBoardCoord(const position coord, tile tile);

        public:
            BoardState() : BoardState("../levels/level_1_1_cpp.csv"){}
            BoardState(std::string level);
            BoardState(std::array<std::array<tile, 20>, 20> temp_game_board, std::array<int, COLOURS> temp_item_count, 
                std::map<position, int> temp_item_list, 
                std::vector<platform> temp_hor_list, std::vector<platform> temp_vert_list) : 
                gameBoard_(temp_game_board), 
                itemCountArr_(temp_item_count), itemMap_(temp_item_list),
                y_PlatformVec(temp_hor_list), x_PlatformVec(x_PlatformVec) {}
            ~BoardState();
            BoardState copy();

            std::vector<platform> GetPlatformVecs(); 
            int GetBoardSize() const { return boardSize_; }
            tile GetBoardPos(position pos) const { return gameBoard_[pos.x][pos.y]; }
            std::array<int, COLOURS> GetItemCount() const { return itemCountArr_; }
            std::array<std::array<tile, 20>, 20> GetBoard() const { return gameBoard_; }
            std::map<position, int> GetItemMap() const { return itemMap_; }


    };
}