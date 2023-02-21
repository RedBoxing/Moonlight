#pragma once

#include "element.hpp"
#include <string>

namespace Starlight
{
    namespace UI
    {
        namespace Elements
        {
            class Title : public Element
            {
            public:
                Title(std::string text, std::string subtitle);

                void render();

            private:
                std::string title;
                std::string subtitle;
            };
        }
    }
}