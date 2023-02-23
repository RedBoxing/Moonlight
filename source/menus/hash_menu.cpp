#include "hash_menu.hpp"

Moonlight::UI::Menus::HashMenu::HashMenu(Starlight::UI::Window *window, std::vector<std::string> &hashes) : Starlight::UI::Elements::Menu(window)
{
    this->addElement(new Starlight::UI::Elements::Title("Hash Menu", "V1.1.0 - PRIVATE"));

    for (auto &hash : hashes)
    {
        this->addElement(new Starlight::UI::Elements::Button(hash, nullptr));
    }
}