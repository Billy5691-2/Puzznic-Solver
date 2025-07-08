#include "../../include/Game/boardState.hpp"

/*
Requirements:
Update platforms
Update items from gravity
Update whether items have been deleted

Generate hash of the board


x = vertical
y = horizontal


*/





namespace Puzznic {
    BoardState::BoardState(std::string level){
        item_count.fill(0);

        std::string data;

        std::fstream levelData(level);
        if (!levelData.is_open()){
            std::cout << "Failed to open file.\n";
        } else {
            std::cout << "File open succeeded. \n";
        }

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
                position temp_pos;
                temp_pos.x = x;
                temp_pos.y = y;

                platform temp_plat;
                temp_plat.pos = temp_pos;
                switch (tile_value) {
                    case 1: //Red
                        temp.item = 1;
                        item_count[RED]++;
                        item_list[temp_pos] = RED;

                        break;
                    case 2: //Blue
                        temp.item = 2;
                        item_count[BLUE]++;
                        item_list[temp_pos] = BLUE;

                        break;
                    case 3: //Green
                        temp.item = 3;
                        item_count[GREEN]++;
                        item_list[temp_pos] = GREEN;

                        break;
                    case 4: //Pink
                        temp.item = 4;
                        item_count[PINK]++;
                        item_list[temp_pos] = PINK;

                        break;
                    case 5: //Purple
                        temp.item = 5;
                        item_count[PURPLE]++;
                        item_list[temp_pos] = PURPLE;

                        break;
                    case 6: //Cyan
                        temp.item = 6;
                        item_count[CYAN]++;
                        item_list[temp_pos] = CYAN;

                        break;
                    case 7: //Brown
                        temp.item = 7;
                        item_count[BROWN]++;
                        item_list[temp_pos] = BROWN;

                        break;
                    case 8: //Orange
                        temp.item = 8;
                        item_count[ORANGE]++;
                        item_list[temp_pos] = ORANGE;

                        break;
                    case 9: // Yellow
                        temp.item = 9;
                        item_count[YELLOW]++;
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
                        vert_plat_list.push_back(temp_plat);
                        break;
                    case 202: //Down
                        temp.platform = 2;
                        temp_plat.direction = POSITIVE;
                        temp_plat.plane = VERTICAL;
                        vert_plat_list.push_back(temp_plat);
                        break;
                    case 203: //Right
                        temp.platform = 3;
                        temp_plat.direction = POSITIVE;
                        temp_plat.plane = HORIZONTAL;
                        hor_plat_list.push_back(temp_plat);
                        break;
                    case 204: //Left
                        temp.platform = 4;
                        temp_plat.direction = NEGATIVE;
                        temp_plat.plane = HORIZONTAL;
                        hor_plat_list.push_back(temp_plat);
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
        //print_item_list();


    }

    BoardState::BoardState(board temp_game_board, std::array<int, COLOURS> temp_item_count, std::map<position, int> temp_item_list, 
                std::vector<platform> temp_hor_list, std::vector<platform> temp_vert_list){
                    game_board = temp_game_board;
                    item_count = temp_item_count;
                    item_list = temp_item_list;
                    hor_plat_list = temp_hor_list;
                    vert_plat_list = temp_vert_list;

                }
    
    BoardState::~BoardState(){

    }

    void BoardState::update_item_count(int colour){
        item_count[colour--]--;
        }
    
    void BoardState::game_loop() {
        update_horizontal_platforms();
        update_vertical_platforms();
        //destroy_items();
        update_items();
        destroy_items();
    }

    void BoardState::update_horizontal_platforms(){
        for (auto platform : hor_plat_list){
            position movement;
            movement.y += platform.direction;
            /*
            switch (platform.direction){
                case POSITIVE:
                    if (!get_board_pos(platform.pos + movement).empty){
                        movement.y = 0;
                        platform.direction = NEGATIVE;
                    }
                    break;
                
                case NEGATIVE:
                    if (!get_board_pos(platform.pos + movement).empty){
                        movement.y = 0;
                        platform.direction = POSITIVE;
                    }
                    break; 
                
                default:
                    std::cout << "Error in update hor platform::boardstate\n";
                }*/
            
            //Possibly a better method for updating horizontal platforms
            if (!move_tile(platform.pos, platform.pos + movement)){
                if (platform.direction == NEGATIVE){
                    platform.direction = POSITIVE;
                } else {
                    platform.direction = NEGATIVE;
                }
            } else {
                platform.pos = platform.pos + movement;
            }
            
            if (movement.y != 0) {
                position new_pos = platform.pos + movement;
                move_tile(platform.pos, new_pos);
                platform.pos = new_pos;
                
                position top_pos = platform.pos;
                bool stack_move = true;
                while (stack_move) {
                    top_pos.x--;
                    if (get_board_pos(top_pos).item){
                        stack_move = move_tile(top_pos, top_pos+movement);
                    } else {
                        stack_move = false;
                    }
                }
            }    
            

        }
    }
    void BoardState::update_vertical_platforms() {
        for (auto platform : vert_plat_list){
            position movement;
            movement.x += platform.direction;
            switch (platform.direction) {
                case POSITIVE:

                    if (move_tile(platform.pos, platform.pos + movement)){
                        position top_pos = platform.pos;
                        platform.pos = platform.pos + movement;
                        bool stack = true;
                        while (stack){
                            top_pos.x--;
                            if (get_board_pos(top_pos).item) {
                                stack = move_item(top_pos, top_pos + movement);
                            } else {
                                stack = false;
                            }
                        }
                    } else {
                        platform.direction = NEGATIVE;
                    }
                    break;
                
                case NEGATIVE:
                    if (get_board_pos(platform.pos + movement).empty) {
                        move_tile(platform.pos, platform.pos + movement);
                        platform.pos = platform.pos + movement;
                        break;

                    } else if (get_board_pos(platform.pos + movement).item) {
                        position stack_top = platform.pos + movement;
                        while (get_board_pos(stack_top).item) {
                            stack_top = stack_top + movement;
                            if (!get_board_pos(stack_top).empty && !get_board_pos(stack_top).item) {
                                movement.x = 0;
                                platform.direction = POSITIVE;
                                break;
                            }
                        }
                        if (movement.x != 0) {
                            bool plat_found = false;
                            while (!plat_found) {
                                stack_top.x++;
                                if (get_board_pos(stack_top).item){
                                    move_item(stack_top, stack_top + movement);
                                } else {
                                    move_tile(stack_top, stack_top + movement);
                                    platform.pos = platform.pos + movement;
                                    plat_found = true;
                                }   
                            } 
                        }
                    } else {
                        platform.direction = POSITIVE;
                        break;
                    }                        
                default:
                    std::cout << "Error in update platform::boardstate\n";
            }
            //Move platform
            //Move items on platform - include falling items


            
        }
    }

    void BoardState::update_items() {
        std::vector <position> changed_items;
        position gravity;
        gravity.x++;
        for (const auto& [key, value] : item_list) {
            if (get_board_pos(key + gravity).empty) {
                changed_items.push_back(key);
            }
        }

        for (auto item : changed_items) {
            move_item(item, item + gravity);
        }
    }

    void BoardState::destroy_items() {
        std::unordered_set<position> deletion_items;
        for (const auto& [key, value] : item_list) {
            for (int i = -1; i <= 1; i += 2) {
                position vertical = key;
                position horizontal = key;
                vertical.x += i;
                horizontal.y += i;
                if (get_board_pos(vertical).item == value) {
                    deletion_items.insert(key);
                } else if (get_board_pos(horizontal).item == value) {
                    deletion_items.insert(key);
                }
                if (deletion_items.count(key)) {
                    break;
                }
            }
        }

        for (const auto& key: deletion_items) {
            update_item_count(item_list[key]);
            tile air;
            air.empty = 1;
            set_board_pos(key, air);
            item_list.erase(key);
        }

    }

    bool BoardState::move_tile(position old_pos, position new_pos) {
        if (!get_board_pos(new_pos).empty) { return false; }
        else {
            set_board_pos(new_pos, get_board_pos(old_pos));
            tile air;
            air.empty = 1;
            set_board_pos(old_pos, air);
            return true;
        }
    }

    bool BoardState::move_item(position old_pos, position new_pos) {
        if (move_tile(old_pos, new_pos)){
            int item = item_list[old_pos];
            item_list.erase(old_pos);
            item_list[new_pos] = item;
            return true;
        } else {
            return false;
        }
    }


    int BoardState::get_board_size(){ return game_board.size; }
    tile BoardState::get_board_pos(position pos){ return game_board.board[pos.x][pos.y]; }
    std::array<int, COLOURS> BoardState::get_item_count(){ return item_count; }
    board BoardState::get_board(){ return game_board; }
    std::map<position, int> BoardState::get_item_list(){ return item_list; }
    std::vector<platform> BoardState::get_platform_list(){ 
        std::vector<platform> output;
        for (auto platform : hor_plat_list){
            output.push_back(platform);
        }
        for (auto platform : vert_plat_list){
            output.push_back(platform);
        }
        return output;
    }

    void BoardState::print_board() {
        for (int i = 0; i < game_board.size; i++) {
            for (int j = 0; j < game_board.size; j++) {
                std::cout << "A" <<game_board.board[i][j].empty << " I"<<game_board.board[i][j].item << " W"<<game_board.board[i][j].wall << " P" << game_board.board[i][j].platform << " ";
            }
        std::cout << "\n";
        } 
    }

    void BoardState::print_item_list(){
        std::cout << "\n Item List Size: " << item_list.size() << "\n";
        std::map<position, int>::iterator it;        
        for (auto const& x : item_list){
            std::cout << "X: " << x.first.x << " Y: " << x.first.y << " Col: " << x.second << "\n";
        }

    }




}
    
