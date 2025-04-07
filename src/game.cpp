#include "../include/game.hpp"
namespace Puzznic {
    Game::Game(std::string level) {
        
        std::string data;

        std::fstream levelData(level);

        std::getline (levelData, data);   
        game_board.size = std::stoi(data);
        std::getline (levelData, data);
        //game_board.width = std::stoi(data);
        
        int x = 0;
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
                switch (tile_value) {
                    case 1: //Red
                        temp.item = 1;
                        break;
                    case 2: //Blue
                        temp.item = 2;
                        break;
                    case 3: //Green
                        temp.item = 3;
                        break;
                    case 4: //Pink
                        temp.item = 4;
                        break;
                    case 5: //Purple
                        temp.item = 5;
                        break;
                    case 6: //Cyan
                        temp.item = 6;
                        break;
                    case 7: //Brown
                        temp.item = 7;
                        break;
                    case 8: //Orange
                        temp.item = 8;
                        break;
                    case 9: // Yellow
                        temp.item = 9;
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
                        break;
                    case 202: //Down
                        temp.platform = 2;
                        break;
                    case 203: //Right
                        temp.platform = 3;
                        break;
                    case 204: //Left
                        temp.platform = 4;
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

    //Game Destructor
    Game::~Game() {
        std::cout << "Close Game 2\n";
    }

    board Game::get_board(){
        return game_board;
    }

    board Game::copy_board(){
        board new_board;
        new_board.size = game_board.size;
        //new_board.height = game_board.height;
        //new_board.width = game_board.width;
        std::copy(&game_board.board[0][0], &game_board.board[0][0]+BOARD_SIZE*BOARD_SIZE, &new_board.board[0][0]);
        return new_board;
    }

    void Game::print_board() {
        for (int i = 0; i < game_board.size; i++) {
            for (int j = 0; j < game_board.size; j++) {
                std::cout << "A" <<game_board.board[i][j].empty << " I"<<game_board.board[i][j].item << " W"<<game_board.board[i][j].wall << " P" << game_board.board[i][j].platform << " ";
            }
        std::cout << "\n";
        } 
    }
}