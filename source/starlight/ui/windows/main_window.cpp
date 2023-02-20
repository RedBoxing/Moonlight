#include "main_window.hpp"
#include "elements/button.hpp"
#include "starlight/hid.hpp"

Starlight::UI::Windows::MainWindow::MainWindow() : Window("Starlight", ImGui::GetMainViewport()->Pos.x, ImGui::GetMainViewport()->Pos.y, 448, ImGui::GetMainViewport()->Size.y, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus, false)
{
    this->addElement(new Starlight::UI::Button("Test", nullptr));
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