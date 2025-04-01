#include "../include/tiles.hpp"
//#include "../include/textureManager.hpp"

namespace GUI{
    void Tiles::init(){
        m_TileProperty = new SDL_Rect;
        *m_TileProperty = {};
        m_TileTexture = NULL;
    }
    
    Tiles::Tiles(SDL_Renderer* p_Renderer, const char* p_FilePath, int p_TileSize){
        init();
        m_Renderer = p_Renderer;
        m_TileTexture = TextureManager::GetTexture(m_Renderer, p_FilePath);
        m_TileProperty->w = p_TileSize;
        m_TileProperty->h = p_TileSize;
    }

    Tiles::~Tiles(){
        delete  m_TileProperty;
        if (m_TileTexture != NULL){
            SDL_DestroyTexture(m_TileTexture);
        }
    }

    void Tiles::setPosition(int p_X, int p_Y){
        m_TileProperty->x = p_X;
        m_TileProperty->y = p_Y;
    }

    void Tiles::draw(){
        TextureManager::Render(m_Renderer, m_TileTexture, m_TileProperty);
        SDL_RenderCopy(m_Renderer, m_TileTexture, NULL, m_TileProperty);
    }

}