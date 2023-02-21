#pragma once

#include "common.hpp"
#include "nn/time.hpp"
#include "ui/menu.hpp"
#include "ui/window.hpp"
#include "ui/elements/element.hpp"
#include "ui/elements/button.hpp"
#include "ui/elements/text.hpp"

namespace Starlight
{
    namespace UI
    {
        inline std::unique_ptr<Starlight::UI::Menu> mainMenu;

        void InitializeHooks();
        bool Initialize();

        void displayNotification(std::string text, nn::TimeSpan duration);

        namespace Utils
        {
            void drawSeparator(int x, int y, int width, int tickness, ImU32 color);
        }
    }
}