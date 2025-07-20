#pragma once
#include "boardState.hpp"
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_set>
#include <array>


namespace Puzznic {
    class HumanPlayer{
        private:
            std::shared_ptr<BoardState> activeBoard_;
            std::map<Coord, std::vector<Move>> availableMoves_; //key is final position
            Coord lastItemSeen_;
            
            void MakeMove(std::vector<Move> moves);
            void GenerateAvailableMoves(Coord item);
            bool ItemInItemList(Coord item);

        public:
            HumanPlayer(std::string level);

            const bool CheckMove(const Move& move);
            void MakeMove(const Move& move);
            const std::map<Coord, std::vector<Move>>& GetAvailableMoves();

            const BoardArr& GetBoard() const { return activeBoard_->GetBoard(); }
            const std::array<int, COLOURS>& GetItemCount() const { return activeBoard_->GetItemCount(); }
            const std::map<Coord, int>& GetItemList() const { return activeBoard_->GetItemMap(); }
            const std::vector<Platform>& GetPlatformList() const { return activeBoard_->GetPlatformVecs(); }
            const int GetBoardSize() const { return activeBoard_->GetBoardSize(); }

            const bool GetWinState() const { return activeBoard_->GetWinState(); }
            const bool GetLoseState() const { return activeBoard_->GetLoseState(); }

            const std::map<Coord, int> GetRenderItems();
            int PositionToID(Coord pos);

    };
}