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

            bool isFocused();
            void setFocused(bool focused);

        private:
            std::vector<Window *> windows;
        };
    }
}