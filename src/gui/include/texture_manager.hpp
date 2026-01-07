#ifndef C9926753_4601_4BBC_A18B_95D28733B4E7
#define C9926753_4601_4BBC_A18B_95D28733B4E7

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <memory>
#include "../../common/enums.hpp"
#include "../../common/file_paths.hpp"

namespace GUI {

    enum TextureType {
        TEX_ITEM,
        TEX_PLATFORM,
        TEX_WALL,
        TEX_MISC,
    };

    class TextureManager {
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_ITEMS> itemTextures_;
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_WALL_TYPES> wallTextures_;
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_PLATFORM_TYPES> platformTextures_;
        std::array<std::shared_ptr<SDL_Texture>, NUMBER_OF_MISC_TYPES> miscTextures_;
        std::shared_ptr<SDL_Renderer> renderHandler_;

        std::shared_ptr<SDL_Texture> GenerateItemTexture(ItemType itemType, const std::string& basePath);
        std::shared_ptr<SDL_Texture> GeneratePlatformTexture(PlatformType platformType, const std::string& basePath);
        std::shared_ptr<SDL_Texture> GenerateWallTexture(WallType wallType, const std::string& basePath);
        std::shared_ptr<SDL_Texture> GenerateMiscTexture(MiscType MiscType, const std::string& basePath);
        std::shared_ptr<SDL_Texture> GenerateTexture(const char* filePath);

        public:
        TextureManager();
        explicit TextureManager(const std::shared_ptr<SDL_Renderer>& renderHandler, const std::string& basePath);
        std::shared_ptr<SDL_Texture> GetTexturePtr(TextureType type, int subType);
        std::shared_ptr<SDL_Texture> GetTexture(ItemType itemType);
        std::shared_ptr<SDL_Texture> GetTexture(PlatformType platformType);
        std::shared_ptr<SDL_Texture> GetTexture(WallType wallType);
        std::shared_ptr<SDL_Texture> GetTexture(MiscType MiscType);

        void Render(const std::shared_ptr<SDL_Texture>& texture, const SDL_Rect& shape);
    };

} // namespace GUI

#endif /* C9926753_4601_4BBC_A18B_95D28733B4E7 */
