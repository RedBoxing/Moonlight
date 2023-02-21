#pragma once

#include "common.hpp"
#include "nn/time.hpp"
#include "ui/menu.hpp"
#include "ui/window.hpp"
#include "ui/elements/element.hpp"
#include "ui/elements/button.hpp"
#include "ui/elements/title.hpp"

namespace Starlight
{
    namespace UI
    {
        inline std::unique_ptr<Starlight::UI::Menu> mainMenu;

        void InitializeHooks();
        bool Initialize();

        void displayNotification(std::string text, nn::TimeSpan duration);
        void clearNotifications();

        namespace Utils
        {
            void drawSeparator(float x, float y, float width, float tickness, ImU32 color);
        }
    }
}