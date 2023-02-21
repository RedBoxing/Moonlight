#include "main_window.hpp"
#include "elements/button.hpp"
#include "starlight/hid.hpp"
#include "starlight/ui.hpp"

Starlight::UI::Windows::MainWindow::MainWindow() : Window("Starlight", 0, 0, 448, 720, false)
{
    this->setTitleBar(false);
    this->setCollapse(false);
    this->setResize(false);
    this->setMove(false);
    this->setBringToFront(true);
    this->setNavFocus(true);

    this->addElement(new Starlight::UI::Elements::Title("Starlight", "V1.1.0 - PRIVATE"));

    this->addElement(new Starlight::UI::Elements::Button("Test Notification", []()
                                                         { Starlight::UI::displayNotification("Loaded Starlight!", nn::TimeSpan::FromMilliSeconds(2500)); }));

    this->addElement(new Starlight::UI::Elements::Button("Test Notification 2", []()
                                                         { Starlight::UI::displayNotification("Failed to place building!", nn::TimeSpan::FromMilliSeconds(2500)); }));

    this->addElement(new Starlight::UI::Elements::Button("Clear Notifications", []()
                                                         { Starlight::UI::clearNotifications(); }));
}

void Starlight::UI::Windows::MainWindow::handleInputs()
{
    if (!this->isEnabled() && Starlight::HID::isButtonHold(nn::hid::NpadButton::ZL) && Starlight::HID::isButtonHold(nn::hid::NpadButton::ZR))
    {
        this->setEnabled(true);
    }
    else if (this->isEnabled() && Starlight::HID::isButtonHold(nn::hid::NpadButton::B))
    {
        this->setEnabled(false);
    }
}

void Starlight::UI::Windows::MainWindow::onEnable()
{
    Starlight::UI::mainMenu->setFocused(true);
}

void Starlight::UI::Windows::MainWindow::onDisable()
{
    Starlight::UI::mainMenu->setFocused(false);
}