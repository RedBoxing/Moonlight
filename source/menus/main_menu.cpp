#include "main_menu.hpp"
#include "logger.hpp"
#include "nn/settings.hpp"

Moonlight::UI::Menus::MainMenu::MainMenu(Starlight::UI::Window *window) : Starlight::UI::Elements::Menu(window)
{
    this->addElement(new Starlight::UI::Elements::Title("Main Menu", "V1.1.0 - PRIVATE"));
    this->addElement(new Starlight::UI::Elements::Button("Notif test 1", [this]()
                                                         { Starlight::UI::displayNotification("Loaded Moonlight!", nn::TimeSpan::FromMilliSeconds(2500)); }));
    this->addElement(new Starlight::UI::Elements::Button("Notif test 2", [this]()
                                                         { Starlight::UI::displayNotification("Failed to place building: You are retarded", nn::TimeSpan::FromMilliSeconds(2500)); }));

    this->addElement(new Starlight::UI::Elements::Button("Logger test", [this]()
                                                         { Moonlight::Logger::log("Hello from Main Menu!"); }));

    this->addElement(new Starlight::UI::Elements::Button("Keyboard Test", [this]()
                                                         {
        char* buffer = (char*)malloc(0x20);
        Starlight::UI::showKeyboard(buffer, 0x20, "Header text", "subText", "guide text", nn::swkbd::KeyboardMode::ModeFull);
        Starlight::UI::displayNotification(std::string(buffer), nn::TimeSpan::FromMilliSeconds(2500)); }));

    /* this->addElement(new Starlight::UI::Elements::Button(std::string("Show Serial Number"), [this]()
                                                          {
                                                             nn::settings::system::SerialNumber *serial = nullptr;
     nn::settings::detail::GetSerialNumber(serial);
     Starlight::UI::displayNotification(std::string(serial->serialNumber), nn::TimeSpan::FromSeconds(5)); }));*/
}