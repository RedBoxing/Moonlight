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
    this->setBringToFront(false);
    this->setNavFocus(false);

    this->addElement(new Starlight::UI::Elements::Button("Test", []()
                                                         { Starlight::UI::displayNotification("Test", nn::TimeSpan::FromSeconds(5)); }));
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