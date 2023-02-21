#pragma once

#include "element.hpp"
#include <string>
namespace Starlight
{
    namespace UI
    {
        namespace Elements
        {
            class Text : public Element
            {
            public:
                Text(std::string text);

                void render();

            private:
                std::string text;
            };
        }
    }
}