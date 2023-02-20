#pragma once

#include "elements/element.hpp"
#include "imgui/imgui.h"
#include <string>
#include <vector>

namespace Starlight
{
    namespace UI
    {
        class Window
        {
        public:
            Window(std::string title, int x, int y, int width, int height, ImGuiWindowFlags flags, bool enabledDefault = true);
            ~Window();

            void render();
            void handleInputs();

            bool isEnabled();
            void setEnabled(bool enabled);

            void addElement(Element *element);

        private:
            std::string title;
            int x;
            int y;
            int width;
            int height;
            ImGuiWindowFlags flags;
            std::vector<Element *> elements;
            bool enabled;
        };
    }
}