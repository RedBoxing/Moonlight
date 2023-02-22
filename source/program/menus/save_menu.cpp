#include "save_menu.hpp"

Moonlight::UI::Menus::SaveMenu::SaveMenu(Starlight::UI::Window *window) : Starlight::UI::Elements::Menu(window)
{
    this->addElement(new Starlight::UI::Elements::Title("Save Menu", "V1.1.0 - PRIVATE"));
    this->addElement(new Starlight::UI::Elements::Button("Back", [this]()
                                                         { this->back(); }));
}