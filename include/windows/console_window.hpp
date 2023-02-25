#pragma once

#include "starlight.hpp"
#include <string>
#include <vector>

namespace Moonlight
{
    namespace UI
    {
        namespace Windows
        {
            class ConsoleWindow : public Starlight::UI::Window
            {
            public:
                ConsoleWindow();
            };
        }

        namespace Elements
        {
            class Console : public Starlight::UI::Elements::Element
            {
            public:
                Console();
                void render() override;

            private:
                std::vector<std::string> history;

                void loggerCallback(const char *line);
            };
        }
    }
}