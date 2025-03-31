#include "../include/board.hpp"
namespace GUI {
    Board::Board(position board_data, SDL_Renderer* p_Renderer){
        m_height = board_data.x;
        m_width = board_data.y;
        m_Renderer = p_Renderer;


    }
    
    
    void Board::drawBoard(){

        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                SDL_Rect _block;
                _block.x = i* tile_size;
                _block.y = j* tile_size;
                _block.w = _block.h = tile_size;
                SDL_SetRenderDrawColor(m_Renderer, 255,255,255,255);
                SDL_RenderFillRect(m_Renderer, &_block);
            }
        }
    }
}