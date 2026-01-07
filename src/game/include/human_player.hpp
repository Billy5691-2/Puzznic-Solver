// #ifndef D406E18E_1373_4615_B3D3_9A1C39330A61
// #define D406E18E_1373_4615_B3D3_9A1C39330A61
// #include "boardState.hpp"
// #include <memory>
// #include <algorithm>
// #include <vector>
// #include <map>
// #include <unordered_set>
// #include <array>


// namespace Puzznic {
//     class HumanPlayer{
//         private:
//             std::shared_ptr<BoardState> activeBoard_;
//             std::map<Coord_t, std::vector<Move>> availableMoves_; //key is final position
//             Coord_t lastItemSeen_;

//             void MakeMove(std::vector<Move> moves);
//             void GenerateAvailableMoves(Coord_t item);
//             bool ItemInItemList(Coord_t item);

//         public:
//             HumanPlayer(std::string level);

//             const bool CheckMove(const Move& move);
//             void MakeMove(const Move& move);
//             const std::map<Coord_t, std::vector<Move>>& GetAvailableMoves();

//             const BoardArr& GetBoard() const { return activeBoard_->GetBoard(); }
//             const std::array<int, COLOURS>& GetItemCount() const { return activeBoard_->GetItemCount(); }
//             const std::map<Coord_t, int>& GetItemList() const { return activeBoard_->GetItemMap(); }
//             const std::vector<Platform_t>& GetPlatformList() const { return activeBoard_->GetPlatformVecs(); }
//             const int GetBoardSize() const { return activeBoard_->GetBoardSize(); }

//             const bool GetWinState() const { return activeBoard_->GetWinState(); }
//             const bool GetLoseState() const { return activeBoard_->GetLoseState(); }

//             const std::map<Coord_t, int> GetRenderItems();
//             int PositionToID(Coord_t pos);

//     };
// }


// #endif /* D406E18E_1373_4615_B3D3_9A1C39330A61 */
