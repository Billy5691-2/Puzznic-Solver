// #include <cassert>
// #include "include/boardState.hpp"

// /*
// Requirements:
// Update platforms
// Update items from gravity
// Update whether items have been deleted

// Generate hash of the board


// x = vertical, 0 top
// y = horizontal, 0 left


// */

// namespace Puzznic {
//     BoardState::BoardState(std::string level) {
//         itemCountArr_.fill(0);

//         std::string data;

//         std::fstream levelData(level);
//         if (!levelData.is_open()) {
//             std::cout << "Failed to open file.\n";
//             assert(false == true);
//         }

//         std::getline(levelData, data);
//         boardSize_ = std::stoi(data);

//         std::getline(levelData, data);

//         int x = 0;
//         while (std::getline(levelData, data) && x < kBoardSize) {
//             int y = 0;
//             std::stringstream ss(data);
//             std::string cell;
//             while (std::getline(ss, cell, ',')) {
//                 if (y >= kBoardSize) {
//                     std::cout << "y out of bounds in read file";
//                 }

//                 int tile_value = std::stoi(cell);
//                 Tile temp;
//                 Coord_t temp_pos;
//                 temp_pos.x = x;
//                 temp_pos.y = y;

//                 Platform_t temp_plat;
//                 temp_plat.pos = temp_pos;
//                 switch (tile_value) {
//                     case 1: // Red
//                         temp.item = 1;
//                         itemCountArr_[RED]++;
//                         itemMap_[temp_pos] = RED;

//                         break;
//                     case 2: // Blue
//                         temp.item = 2;
//                         itemCountArr_[BLUE]++;
//                         itemMap_[temp_pos] = BLUE;

//                         break;
//                     case 3: // Green
//                         temp.item = 3;
//                         itemCountArr_[GREEN]++;
//                         itemMap_[temp_pos] = GREEN;

//                         break;
//                     case 4: // Pink
//                         temp.item = 4;
//                         itemCountArr_[PINK]++;
//                         itemMap_[temp_pos] = PINK;

//                         break;
//                     case 5: // Purple
//                         temp.item = 5;
//                         itemCountArr_[PURPLE]++;
//                         itemMap_[temp_pos] = PURPLE;

//                         break;
//                     case 6: // Cyan
//                         temp.item = 6;
//                         itemCountArr_[CYAN]++;
//                         itemMap_[temp_pos] = CYAN;

//                         break;
//                     case 7: // Brown
//                         temp.item = 7;
//                         itemCountArr_[BROWN]++;
//                         itemMap_[temp_pos] = BROWN;

//                         break;
//                     case 8: // Orange
//                         temp.item = 8;
//                         itemCountArr_[ORANGE]++;
//                         itemMap_[temp_pos] = ORANGE;

//                         break;
//                     case 9: // Yellow
//                         temp.item = 9;
//                         itemCountArr_[YELLOW]++;
//                         itemMap_[temp_pos] = YELLOW;

//                         break;

//                     case 101: // Exterior
//                         temp.wall = 1;
//                         break;
//                     case 102: // Floor
//                         temp.wall = 2;
//                         break;
//                     case 103: // Ledge
//                         temp.wall = 3;
//                         break;
//                     case 104: // Interior
//                         temp.wall = 4;
//                         break;
//                     case 105:
//                         temp.wall = 5;
//                         break;

//                     case 201: // Up
//                         temp.platform = 1;
//                         temp_plat.direction = NEGATIVE;
//                         temp_plat.plane = VERTICAL;
//                         x_PlatformVec.push_back(temp_plat);
//                         break;
//                     case 202: // Down
//                         temp.platform = 2;
//                         temp_plat.direction = POSITIVE;
//                         temp_plat.plane = VERTICAL;
//                         x_PlatformVec.push_back(temp_plat);
//                         break;
//                     case 203: // Right
//                         temp.platform = 3;
//                         temp_plat.direction = POSITIVE;
//                         temp_plat.plane = HORIZONTAL;
//                         y_PlatformVec.push_back(temp_plat);
//                         break;
//                     case 204: // Left
//                         temp.platform = 4;
//                         temp_plat.direction = NEGATIVE;
//                         temp_plat.plane = HORIZONTAL;
//                         y_PlatformVec.push_back(temp_plat);
//                         break;

//                     case 999: // Empty
//                         temp.empty = 1;
//                         break;

//                     default:
//                         std::cout << "Error in file read";
//                 }
//                 gameBoard_[x][y] = temp;
//                 y++;
//             }
//             x++;
//         }
//         levelData.close();

//         /* Deugging
//         print_board();
//         //print_item_list();
//         */
//     }

//     /*BoardState::BoardState(board temp_game_board, std::array<int, COLOURS> temp_item_count,
//         std::map<Coord_t, int> temp_item_list,
//                 std::vector<Platform_t> temp_hor_list, std::vector<Platform_t> temp_vert_list){
//                     gameBoard_ = temp_game_board;
//                     itemCountArr_ = temp_item_count;
//                     item_list = temp_item_list;
//                     y_PlatformVec = temp_hor_list;
//                     x_PlatformVec = temp_vert_list;

//                 }*/

//     BoardState::~BoardState() {
//         std::cout << "Board destroyed";
//     }

//     BoardState BoardState::copy() {
//         return BoardState(gameBoard_, itemCountArr_, itemMap_, y_PlatformVec, x_PlatformVec);
//     }

//     void BoardState::UpdateItemCount(int colour) {
//         itemCountArr_[colour--]--;
//     }

//     bool BoardState::GameLoop(Move move) {
//         Coord_t old_pos = move.original;
//         Coord_t new_pos = move.updated;

//         movesToHere_.push_back(move);

//         if (!(old_pos.x == kBoardSize && old_pos.y == kBoardSize)) {
//             MoveItem(old_pos, new_pos);
//         }
//         UpdateY_Platforms();
//         UpdateX_Platforms();
//         // MatchItems();
//         UpdateItems();
//         MatchItems();
//         return GameFinished();
//     }

//     void BoardState::UpdateY_Platforms() {
//         for (auto platform : y_PlatformVec) {
//             Coord_t movement;
//             movement.y += platform.direction;

//             if (!MoveTile(platform.pos, platform.pos + movement)) {
//                 if (platform.direction == NEGATIVE) {
//                     platform.direction = POSITIVE;
//                 } else {
//                     platform.direction = NEGATIVE;
//                 }
//             } else {
//                 platform.pos = platform.pos + movement;
//             }

//             if (movement.y != 0) {
//                 Coord_t new_pos = platform.pos + movement;
//                 MoveTile(platform.pos, new_pos);
//                 platform.pos = new_pos;

//                 Coord_t top_pos = platform.pos;
//                 bool stack_move = true;
//                 while (stack_move) {
//                     top_pos.x--;
//                     if (GetBoardPos(top_pos).item) {
//                         stack_move = MoveTile(top_pos, top_pos + movement);
//                     } else {
//                         stack_move = false;
//                     }
//                 }
//             }
//         }
//     }

//     void BoardState::UpdateX_Platforms() {
//         for (auto platform : x_PlatformVec) {
//             Coord_t movement;
//             movement.x += platform.direction;
//             switch (platform.direction) {
//                 case POSITIVE:

//                     if (MoveTile(platform.pos, platform.pos + movement)) {
//                         Coord_t top_pos = platform.pos;
//                         platform.pos = platform.pos + movement;
//                         bool stack = true;
//                         while (stack) {
//                             top_pos.x--;
//                             if (GetBoardPos(top_pos).item) {
//                                 stack = MoveItem(top_pos, top_pos + movement);
//                             } else {
//                                 stack = false;
//                             }
//                         }
//                     } else {
//                         platform.direction = NEGATIVE;
//                     }
//                     break;

//                 case NEGATIVE:
//                     if (GetBoardPos(platform.pos + movement).empty) {
//                         MoveTile(platform.pos, platform.pos + movement);
//                         platform.pos = platform.pos + movement;
//                         break;
//                     } else if (GetBoardPos(platform.pos + movement).item) {
//                         Coord_t stack_top = platform.pos + movement;
//                         while (GetBoardPos(stack_top).item) {
//                             stack_top = stack_top + movement;
//                             if (!GetBoardPos(stack_top).empty && !GetBoardPos(stack_top).item) {
//                                 movement.x = 0;
//                                 platform.direction = POSITIVE;
//                                 break;
//                             }
//                         }
//                         if (movement.x != 0) {
//                             bool plat_found = false;
//                             while (!plat_found) {
//                                 stack_top.x++;
//                                 if (GetBoardPos(stack_top).item) {
//                                     MoveItem(stack_top, stack_top + movement);
//                                 } else {
//                                     MoveTile(stack_top, stack_top + movement);
//                                     platform.pos = platform.pos + movement;
//                                     plat_found = true;
//                                 }
//                             }
//                         }
//                     } else {
//                         platform.direction = POSITIVE;
//                         break;
//                     }
//                 default:
//                     assert(false == true);
//                     std::cout << "Error in update platform::boardstate\n";
//             }
//             // Move platform
//             // Move items on platform - include falling items
//         }
//     }

//     void BoardState::UpdateItems() {
//         std::vector<Coord_t> changed_items;
//         Coord_t gravity;
//         gravity.x++;
//         for (const auto& x : itemMap_) {
//             if (GetBoardPos(x.first + gravity).empty) {
//                 changed_items.push_back(x.first);
//             }
//         }

//         for (auto item : changed_items) {
//             MoveItem(item, item + gravity);
//         }
//     }

//     void BoardState::MatchItems() {
//         std::unordered_set<Coord_t> deletion_items;
//         for (const auto& x : itemMap_) {
//             for (int i = -1; i <= 1; i += 2) {
//                 Coord_t vertical = x.first;
//                 Coord_t horizontal = x.first;
//                 vertical.x += i;
//                 horizontal.y += i;
//                 if (GetBoardPos(vertical).item == x.second) {
//                     deletion_items.insert(x.first);
//                 } else if (GetBoardPos(horizontal).item == x.second) {
//                     deletion_items.insert(x.first);
//                 }
//                 if (deletion_items.count(x.first)) {
//                     break;
//                 }
//             }
//         }

//         for (const auto& key : deletion_items) {
//             UpdateItemCount(itemMap_[key]);
//             Tile air;
//             air.empty = 1;
//             SetBoardCoord(key, air);
//             itemMap_.erase(key);
//         }
//     }

//     bool BoardState::GameFinished() {
//         bool won = true;
//         for (const auto& count : itemCountArr_) {
//             if (count == 1) {
//                 gameLost_ = true;
//                 return true;
//             }
//             if (count > 0) {
//                 won = false;
//             }
//         }
//         gameWon_ = won;
//         if (won) {
//             return true;
//         }
//         return false;
//     }

//     bool BoardState::MoveTile(Coord_t old_pos, Coord_t new_pos) {
//         if (!GetBoardPos(new_pos).empty) {
//             return false;
//         } else {
//             SetBoardCoord(new_pos, GetBoardPos(old_pos));
//             Tile air;
//             air.empty = 1;
//             SetBoardCoord(old_pos, air);
//             return true;
//         }
//     }

//     bool BoardState::MoveItem(Coord_t old_pos, Coord_t new_pos) {
//         if (MoveTile(old_pos, new_pos)) {
//             int item = itemMap_[old_pos];
//             itemMap_.erase(old_pos);
//             itemMap_[new_pos] = item;
//             return true;
//         } else {
//             return false;
//         }
//     }

//     void BoardState::SetBoardCoord(const Coord_t coord, Tile tile) {
//         gameBoard_[coord.x][coord.y] = tile;
//     }

//     const std::vector<Platform_t>& BoardState::GetPlatformVecs() {
//         std::vector<Platform_t> output;
//         for (auto platform : y_PlatformVec) {
//             output.push_back(platform);
//         }
//         for (auto platform : x_PlatformVec) {
//             output.push_back(platform);
//         }
//         return output;
//     }

// } // namespace Puzznic
