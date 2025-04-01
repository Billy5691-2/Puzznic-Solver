#include "../include/board.hpp"
namespace GUI {
    Board::Board(int board_size, SDL_Renderer* p_Renderer){
        m_Renderer = p_Renderer;
        m_board_size = board_size;
        tile_size = WINDOW_HEIGHT / board_size;


    }
    
    
    void Board::drawBoard(){

        for (int i = 0; i < m_board_size; i++) {
            for (int j = 0; j < m_board_size; j++) {
                SDL_Rect _block;
                _block.x = (i* tile_size) + WINDOW_LEFT;
                _block.y = j* tile_size;
                _block.w = _block.h = tile_size;
                SDL_SetRenderDrawColor(m_Renderer, 0, 20, 45, 30);
                SDL_RenderFillRect(m_Renderer, &_block);
                
                SDL_SetRenderDrawColor(m_Renderer, 0,0,0,255);
                SDL_RenderDrawRect(m_Renderer, &_block);
            }
        }
    }

    int Board::getTileSize(){
        return tile_size;
    }
}