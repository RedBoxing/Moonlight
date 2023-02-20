#include "window.hpp"

Starlight::UI::Window::Window(std::string title, int x, int y, int width, int height, ImGuiWindowFlags flags, bool enabledDefault)
{
    this->title = title;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->flags = flags;
    this->enabled = enabledDefault;
}

Starlight::UI::Window::~Window()
{
    for (Element *element : this->elements)
    {
        delete element;
    }
}

void Starlight::UI::Window::render()
{
    if (this->enabled)
    {
        ImGui::SetNextWindowPos(ImVec2(this->x, this->y));
        ImGui::SetNextWindowSize(ImVec2(this->width, this->height));
        ImGui::Begin(this->title.c_str(), nullptr, this->flags);

        for (Element *element : this->elements)
        {
            element->render();
        }

        ImGui::End();
    }
}

void Starlight::UI::Window::handleInputs()
{
    /* if (this->enabled)
     {
         for (Element *element : this->elements)
         {
             // element->handleInputs();
         }
     }*/
}

bool Starlight::UI::Window::isEnabled()
{
    return this->enabled;
}

void Starlight::UI::Window::setEnabled(bool enabled)
{
    this->enabled = enabled;
}