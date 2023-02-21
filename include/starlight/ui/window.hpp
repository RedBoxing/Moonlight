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
            Window(std::string title, int x, int y, int width, int height, bool enabledDefault = true);

            void render();
            virtual void handleInputs();

            void addElement(Elements::Element *element);

            void setTitleBar(bool enabled);
            void setResize(bool enabled);
            void setMove(bool enabled);
            void setCollapse(bool enabled);
            void setBringToFront(bool enabled);
            void setNavFocus(bool enabled);

            std::string getTitle();
            void setTitle(std::string title);

            int getX();
            void setX(int x);

            int getY();
            void setY(int y);

            int getWidth();
            void setWidth(int width);

            int getHeight();
            void setHeight(int height);

            ImGuiWindowFlags getFlags();
            void setFlags(ImGuiWindowFlags flags);

            std::vector<Elements::Element *> getElements();
            void setElements(std::vector<Elements::Element *> elements);

            bool isEnabled();
            void setEnabled(bool enabled);

            virtual void onEnable();
            virtual void onDisable();

        private:
            std::string title;
            int x;
            int y;
            int width;
            int height;
            ImGuiWindowFlags flags = 0;
            std::vector<Elements::Element *> elements;
            bool enabled;
        };
    }
}