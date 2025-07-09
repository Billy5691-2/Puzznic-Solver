#include "../../include/GUI/board_background.hpp"
namespace GUI {
    BoardBackground::BoardBackground(SDL_Renderer* p_Renderer){
        m_Renderer = p_Renderer;
        tileSize_ = WINDOW_HEIGHT / kBoardSize;
    }
    
    
    void BoardBackground::DrawBackground(){

        for (int i = 0; i < kBoardSize; i++) {
            for (int j = 0; j < kBoardSize; j++) {
                SDL_Rect _block;
                _block.x = (i* tileSize_) + WINDOW_LEFT;
                _block.y = j* tileSize_;
                _block.w = _block.h = tileSize_;
                SDL_SetRenderDrawColor(m_Renderer, 0, 20, 45, 30);
                SDL_RenderFillRect(m_Renderer, &_block);
                
                SDL_SetRenderDrawColor(m_Renderer, 0,0,0,255);
                SDL_RenderDrawRect(m_Renderer, &_block);
            }
        }
    }

    int BoardBackground::GetTileSize(){
        return tileSize_;
    }
}