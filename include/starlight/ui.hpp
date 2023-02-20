#pragma once

#include "common.hpp"
#include "ui/menu.hpp"
#include "ui/elements/element.hpp"
#include "ui/elements/button.hpp"

namespace Starlight
{
    namespace UI
    {
        void InitializeHooks();
        bool Initialize();

        namespace Utils
        {
            void drawSeparator(int x, int y, int width, int tickness, int color);
        }
    }
}