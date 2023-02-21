#include "window.hpp"

Starlight::UI::Window::Window(std::string title, int x, int y, int width, int height, bool enabledDefault)
{
    this->title = title;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->flags = flags;
    this->enabled = enabledDefault;
}

void Starlight::UI::Window::render()
{
    if (this->enabled)
    {
        ImGui::SetNextWindowPos(ImVec2(this->x, this->y));
        ImGui::SetNextWindowSize(ImVec2(this->width, this->height));
        ImGui::Begin(this->title.c_str(), nullptr, this->flags);

        for (Elements::Element *element : this->elements)
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

void Starlight::UI::Window::addElement(Elements::Element *element)
{
    this->elements.push_back(element);
}

void Starlight::UI::Window::setTitleBar(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoTitleBar)
    {
        this->flags &= ~ImGuiWindowFlags_NoTitleBar;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoTitleBar))
    {
        this->flags |= ImGuiWindowFlags_NoTitleBar;
    }
}

void Starlight::UI::Window::setResize(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoResize)
    {
        this->flags &= ~ImGuiWindowFlags_NoResize;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoResize))
    {
        this->flags |= ImGuiWindowFlags_NoResize;
    }
}

void Starlight::UI::Window::setMove(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoMove)
    {
        this->flags &= ~ImGuiWindowFlags_NoMove;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoMove))
    {
        this->flags |= ImGuiWindowFlags_NoMove;
    }
}

void Starlight::UI::Window::setCollapse(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoCollapse)
    {
        this->flags &= ~ImGuiWindowFlags_NoCollapse;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoCollapse))
    {
        this->flags |= ImGuiWindowFlags_NoCollapse;
    }
}

void Starlight::UI::Window::setBringToFront(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoBringToFrontOnFocus)
    {
        this->flags &= ~ImGuiWindowFlags_NoBringToFrontOnFocus;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoBringToFrontOnFocus))
    {
        this->flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    }
}

void Starlight::UI::Window::setNavFocus(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoNavFocus)
    {
        this->flags &= ~ImGuiWindowFlags_NoNavFocus;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoNavFocus))
    {
        this->flags |= ImGuiWindowFlags_NoNavFocus;
    }
}

void Starlight::UI::Window::setScrollbar(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoScrollbar)
    {
        this->flags &= ~ImGuiWindowFlags_NoScrollbar;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoScrollbar))
    {
        this->flags |= ImGuiWindowFlags_NoScrollbar;
    }
}

void Starlight::UI::Window::setFocusOnAppearing(bool enabled)
{
    if (enabled && this->flags & ImGuiWindowFlags_NoFocusOnAppearing)
    {
        this->flags &= ~ImGuiWindowFlags_NoFocusOnAppearing;
    }
    else if (!enabled && !(this->flags & ImGuiWindowFlags_NoFocusOnAppearing))
    {
        this->flags |= ImGuiWindowFlags_NoFocusOnAppearing;
    }
}

std::string Starlight::UI::Window::getTitle()
{
    return this->title;
}

void Starlight::UI::Window::setTitle(std::string title)
{
    this->title = title;
}

int Starlight::UI::Window::getX()
{
    return this->x;
}

void Starlight::UI::Window::setX(int x)
{
    this->x = x;
}

int Starlight::UI::Window::getY()
{
    return this->y;
}

void Starlight::UI::Window::setY(int y)
{
    this->y = y;
}

int Starlight::UI::Window::getWidth()
{
    return this->width;
}

void Starlight::UI::Window::setWidth(int width)
{
    this->width = width;
}

int Starlight::UI::Window::getHeight()
{
    return this->height;
}

void Starlight::UI::Window::setHeight(int height)
{
    this->height = height;
}

ImGuiWindowFlags Starlight::UI::Window::getFlags()
{
    return this->flags;
}

void Starlight::UI::Window::setFlags(ImGuiWindowFlags flags)
{
    this->flags = flags;
}

std::vector<Starlight::UI::Elements::Element *> Starlight::UI::Window::getElements()
{
    return this->elements;
}

void Starlight::UI::Window::setElements(std::vector<Starlight::UI::Elements::Element *> elements)
{
    this->elements = elements;
}

bool Starlight::UI::Window::isEnabled()
{
    return this->enabled;
}

void Starlight::UI::Window::setEnabled(bool enabled)
{
    this->enabled = enabled;
    if (this->enabled)
    {
        this->onEnable();
    }
    else
    {
        this->onDisable();
    }
}