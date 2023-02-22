#include "moonlight_menu.hpp"
#include "windows/main_window.hpp"

Moonlight::UI::Menu::Menu() : Starlight::UI::Menu()
{
    this->addWindow(new Moonlight::UI::Windows::MainWindow());
}