#pragma once

#include "starlight.hpp"

namespace Moonlight
{
    namespace UI
    {
        namespace Menus
        {
            class HashMenu : public Starlight::UI::Elements::Menu
            {
            public:
                HashMenu(Starlight::UI::Window *window, std::vector<std::string> &hashes);
            };
        }
    }
}