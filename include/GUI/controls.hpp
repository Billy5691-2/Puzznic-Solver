#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "tiles.hpp"
#include "../texture_paths.hpp"
#include "../constants.hpp"

namespace GUI {
    class Controls{
        SDL_Renderer* m_Renderer;
        TTF_Font* m_Font_;
        SDL_Colour m_TextColour;

        Tiles* upArrowLvl_;
        Tiles* downArrowLvl_;
        Tiles* upArrowStage_;
        Tiles* downArrowStage_;

        SDL_Surface* loadTextSurface_;
        SDL_Texture* loadTextTexture_;
        SDL_Rect loadTextRect_;

        SDL_Surface* solveTextSurface_;
        SDL_Texture* solveTextTexture_;
        SDL_Rect solveTextRect_;

        SDL_Surface* levelTextSurface_;
        SDL_Texture* levelTextTexture_;

        SDL_Surface* stageTextSurface_;
        SDL_Texture* stageTextTexture_;

        int tileSize_;

        int stage_ = 1;
        int level_ = 1;

        bool solveButtonPressed_ = false;
        bool loadButtonPressed_ = false;

        void DrawLoadButton();
        void DrawSolveButton();
        void DrawText();
        void DrawControls();

        void RenderButtons();
        void RenderText();

        int CheckNumBounds(int value, int change);

        public:
            Controls(SDL_Renderer* p_Renderer, TTF_Font* p_Font, SDL_Colour p_Txt_Colour,
                int p_tile_size);
            ~Controls();

            void Render();
            void Free();
            
            void HandleClick(int x, int y);

            bool GetStartSolver();
            
            bool GetChangeLvl();
            std::string GetLvlFilename();
    };
}