#include "../../include/Game/human_player.hpp"

namespace Puzznic {
    HumanPlayer::HumanPlayer(std::string level){
        activeBoard_ = std::make_shared<BoardState>(level);
    }

    const bool HumanPlayer::CheckMove(const Move& move){
        if (move.original == lastItemSeen_ && ItemInItemList(move.original)){
            if (auto search = availableMoves_.find(move.original); search != availableMoves_.end()){
                activeBoard_->MakeMove(search->second);
                return true;
            }
        } else {
            GenerateAvailableMoves(move.original);
            return false;
        }

    }

    void HumanPlayer::MakeMove(const Move& move){
        activeBoard_->MakeMove(move);
    }

    void HumanPlayer::GenerateAvailableMoves(Coord item){
        availableMoves_.clear();
        if (ItemInItemList(item)){
            std::unordered_set<BoardArr, BoardHasher> seenBoards;
            
            //to do
        }
    }

    bool HumanPlayer::ItemInItemList(Coord item){
        if (auto search = GetItemList().find(item); search != GetItemList().end()){
            return true;
        } else {
            return false;
        }
    }

    const std::map<Coord, int> HumanPlayer::GetRenderItems(){
        const std::map<int, Item> ItemIds = activeBoard_->GetItemMap();
        std::map<Coord, int> ItemCoordsMap;
        for (const auto& [key, value] : ItemIds){
            if (!value.deleted) {
                ItemCoordsMap[value.position] = value.colour;
            }
        }
        return ItemCoordsMap;
    }

    int PositionToId(Coord pos){
        const std::map<int, Item> ItemIds = activeBoard_->GetItemMap();
        for (const auto& [key, value] : ItemIds){
            if (pos == value.position){
                return key;
            }
        }
    }
}