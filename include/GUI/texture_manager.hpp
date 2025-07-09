#pragma once
#include <SDL2/SDL_image.h>
//#include <cstddef>

namespace  GUI  {
    class TextureManager{
        public:
            static SDL_Texture* GetTexture(SDL_Renderer* p_Renderer, const char *p_FilePath);
            static void Render(SDL_Renderer* p_Renderer, SDL_Texture* p_Texture, 
                    SDL_Rect* p_DsntRect);
    };

    
}