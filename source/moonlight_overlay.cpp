#include "moonlight_overlay.hpp"
#include "menus/main_menu.hpp"
#include "windows/console_window.hpp"

Moonlight::UI::Overlay::Overlay() : Starlight::UI::Overlay()
{
    this->addWindow(Starlight::UI::Windows::MenuWindow::create<Moonlight::UI::Menus::MainMenu>(this));
    // this->addWindow(new Moonlight::UI::Windows::ConsoleWindow());
}