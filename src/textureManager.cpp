#include "../include/textureManager.hpp"

namespace GUI{
    SDL_Texture* TextureManager::GetTexture(SDL_Renderer* p_Renderer, const char *p_FilePath){
        SDL_Texture* _texture = IMG_LoadTexture(p_Renderer, p_FilePath);
        if (_texture == NULL) {
            SDL_Log("Failed to load img from %s \n " 
                    " {ERROR: %s} \n", p_FilePath, SDL_GetError());
            return NULL;
        }
        return _texture;
    }

    void TextureManager::Render(SDL_Renderer* p_Renderer, SDL_Texture* p_Texture,
            SDL_Rect* p_DsntRect){
                SDL_RenderCopy(p_Renderer, p_Texture, NULL, p_DsntRect);
            }
}