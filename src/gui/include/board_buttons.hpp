#ifndef CB903CCF_5D24_4C7E_9C94_093182ACA443
#define CB903CCF_5D24_4C7E_9C94_093182ACA443

#include <memory>
#include "gui_data.hpp"
#include "structs.hpp"

namespace GUI {
    class BoardButtons {
        static bool CheckItemsClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord& gridPos);
        static bool CheckMovesClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord& gridPos);
        static Coord ConvertToGrid(const Coord& pixelPos);

        public:
        static void CheckClicked(const std::shared_ptr<RenderData_t>& renderData, const Coord& pixelPos);
    };
} // namespace GUI

#endif /* CB903CCF_5D24_4C7E_9C94_093182ACA443 */
