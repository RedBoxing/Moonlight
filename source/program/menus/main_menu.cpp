#include "main_menu.hpp"
#include "save_menu.hpp"

Moonlight::UI::Menus::MainMenu::MainMenu(Starlight::UI::Window *window) : Starlight::UI::Elements::Menu(window)
{
    this->addElement(new Starlight::UI::Elements::Title("Main Menu", "V1.1.0 - PRIVATE"));
    this->addElement(new Starlight::UI::Elements::Button("Save Menu", [this]()
                                                         { this->switchTo(new Moonlight::UI::Menus::SaveMenu(this->getWindow())); }));
    this->addElement(new Starlight::UI::Elements::Button("Notif test 1", [this]()
                                                         { Starlight::UI::displayNotification("Loaded Moonlight!", nn::TimeSpan::FromMilliSeconds(2500)); }));
    this->addElement(new Starlight::UI::Elements::Button("Notif test 2", [this]()
                                                         { Starlight::UI::displayNotification("Failed to place building: You are retarded", nn::TimeSpan::FromMilliSeconds(2500)); }));
    this->addElement(new Starlight::UI::Elements::Button("Back", [this]()
                                                         { this->back(); }));
}