#pragma once

#include "element.hpp"
#include <string>
#include <functional>

namespace Starlight
{
    namespace UI
    {
        class Button : public Element
        {
        public:
            Button(std::string text, std::function<void()> onClick);
            ~Button();

            void render();

        private:
            std::string text;
            std::function<void()> onClick;
        };
    }
}