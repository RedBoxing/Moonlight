#pragma once

#include "window.hpp"
#include <vector>

namespace Starlight
{
    namespace UI
    {
        class Menu
        {
        public:
            Menu();
            ~Menu();

            void Initialize();
            void update();

        private:
            std::vector<Window *> windows;
        };
    }
}