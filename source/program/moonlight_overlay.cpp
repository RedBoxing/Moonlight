#include "moonlight_overlay.hpp"
#include "menus/main_menu.hpp"

Moonlight::UI::Overlay::Overlay() : Starlight::UI::Overlay()
{
    this->addWindow(Starlight::UI::Windows::MenuWindow::create<Moonlight::UI::Menus::MainMenu>(this));
}