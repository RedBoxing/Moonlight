#pragma once

#include "starlight.hpp"

namespace Moonlight
{
    namespace UI
    {
        namespace Menus
        {
            class MainMenu : public Starlight::UI::Elements::Menu
            {
            public:
                MainMenu(Starlight::UI::Window *window);
            };
        }
    }
}