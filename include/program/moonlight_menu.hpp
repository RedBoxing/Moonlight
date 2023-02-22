#pragma once

#include "starlight.hpp"

namespace Moonlight
{
    namespace UI
    {
        class Menu : public Starlight::UI::Menu
        {
        public:
            Menu();
        };

        inline Moonlight::UI::Menu *g_menu = nullptr;
    }
}