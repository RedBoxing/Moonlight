#pragma once

#include "starlight.hpp"

namespace Moonlight
{
    namespace UI
    {
        namespace Menus
        {
            class SaveMenu : public Starlight::UI::Elements::Menu
            {
            public:
                SaveMenu(Starlight::UI::Window *window);
            };
        }
    }
}