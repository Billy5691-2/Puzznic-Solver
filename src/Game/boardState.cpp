#include "../../include/Game/boardState.hpp"

namespace Puzznic {
    BoardState::BoardState(std::string level){
        std::array<int, COLOURS> item_count; 
        item_count.fill(0);

        std::map<position, int> item_list;

        std::string data;

        std::fstream levelData(level);

        std::getline (levelData, data);   
        game_board.size = std::stoi(data);
        std::getline (levelData, data);
        //game_board.width = std::stoi(data);
        
        int x = 0;
        int platform_id = 0;
        while (std::getline (levelData, data) && x < BOARD_SIZE) {

            int y = 0;
            std::stringstream ss(data);
            std::string cell;
            while (std::getline (ss, cell, ',')) {
                if (y >= BOARD_SIZE){
                    std::cout << "y out of bounds in read file";
                }

                int tile_value = std::stoi(cell);
                tile temp; 
                position temp_pos;
                temp_pos.x = x;
                temp_pos.y = y;

                platform temp_plat;
                temp_plat.pos = temp_pos;

                switch (tile_value) {
                    case 1: //Red
                        temp.item = 1;
                        item_count[0]++;
                        item_list[temp_pos] = RED;
                        break;
                    case 2: //Blue
                        temp.item = 2;
                        item_count[1]++;
                        item_list[temp_pos] = BLUE;
                        break;
                    case 3: //Green
                        temp.item = 3;
                        item_count[2]++;
                        item_list[temp_pos] = GREEN;
                        break;
                    case 4: //Pink
                        temp.item = 4;
                        item_count[3]++;
                        item_list[temp_pos] = PINK;
                        break;
                    case 5: //Purple
                        temp.item = 5;
                        item_count[4]++;
                        item_list[temp_pos] = PURPLE;
                        break;
                    case 6: //Cyan
                        temp.item = 6;
                        item_count[5]++;
                        item_list[temp_pos] = CYAN;
                        break;
                    case 7: //Brown
                        temp.item = 7;
                        item_count[5]++;
                        item_list[temp_pos] = BROWN;
                        break;
                    case 8: //Orange
                        temp.item = 8;
                        item_count[6]++;
                        item_list[temp_pos] = ORANGE;
                        break;
                    case 9: // Yellow
                        temp.item = 9;
                        item_count[7]++;
                        item_list[temp_pos] = YELLOW;
                        break;
                    
                    case 101: //Exterior
                        temp.wall = 1;
                        break;
                    case 102: //Floor
                        temp.wall = 2;
                        break;
                    case 103: //Ledge
                        temp.wall = 3;
                        break;
                    case 104: //Interior
                        temp.wall = 4;
                        break;
                    case 105:
                        temp.wall = 5;
                        break;
                    
                    case 201: //Up
                        temp.platform = 1;
                        temp_plat.direction = NEGATIVE;
                        temp_plat.plane = VERTICAL;
                        platform_list[platform_id] = temp_plat;
                        platform_id++;
                        break;
                    case 202: //Down
                        temp.platform = 2;
                        temp_plat.direction = POSITIVE;
                        temp_plat.plane = VERTICAL;
                        platform_list[platform_id] = temp_plat;
                        platform_id++;
                        break;
                    case 203: //Right
                        temp.platform = 3;
                        temp_plat.direction = POSITIVE;
                        temp_plat.plane = HORIZONTAL;
                        platform_list[platform_id] = temp_plat;
                        platform_id++;
                        break;
                    case 204: //Left
                        temp.platform = 4;
                        temp_plat.direction = NEGATIVE;
                        temp_plat.plane = HORIZONTAL;
                        platform_list[platform_id] = temp_plat;
                        platform_id++;
                        break;

                    case 999: //Empty
                        temp.empty = 1;
                        break;

                    default:
                        std::cout << "Error in file read";
                        
                }
                game_board.board[x][y] = temp;
                y++;
                
            }
            x++;

        }
        levelData.close();/**/

        //print_board();


    }
    BoardState::BoardState(board temp_game_board, std::array<int, COLOURS> temp_item_count, std::map<position, int> temp_item_list, 
                std::map<int, platform> temp_platform_list){
                    game_board = temp_game_board;
                    item_count = temp_item_count;
                    item_list = temp_item_list;
                    platform_list = temp_platform_list;

                }
    
    BoardState::~BoardState(){

    }

    void BoardState::update_item_count(int colour){
        item_count[colour--]--;
        /*
        std::map<position, int>::iterator it;
        for (it = item_list.begin(); it != item_list.end(); it++){
            item_count[(it->second) - 1]++;
        }*/
        }

    int BoardState::get_board_size(){ return game_board.size; }
    tile BoardState::get_board_pos(position pos){ return game_board.board[pos.x][pos.y]; }
    std::array<int, COLOURS> BoardState::get_item_count(){ return item_count; }
    board BoardState::get_board(){ return game_board; }
    std::map<position, int> BoardState::get_item_list(){ return item_list; }
    std::map<int, platform> BoardState::get_platform_list(){ return platform_list; }

    void BoardState::print_board() {
        for (int i = 0; i < game_board.size; i++) {
            for (int j = 0; j < game_board.size; j++) {
                std::cout << "A" <<game_board.board[i][j].empty << " I"<<game_board.board[i][j].item << " W"<<game_board.board[i][j].wall << " P" << game_board.board[i][j].platform << " ";
            }
        std::cout << "\n";
        } 
    }




}
    
