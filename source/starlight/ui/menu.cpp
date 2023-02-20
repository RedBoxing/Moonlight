#include "menu.hpp"
#include "windows/main_window.hpp"
#include "starlight/hid.hpp"
#include "imgui/imgui_impl_nvn.hpp"

void Starlight::UI::Menu::Initialize()
{
    this->windows.push_back(new Windows::MainWindow());
}

void Starlight::UI::Menu::update()
{
    Starlight::HID::updatePadState();

    ImguiNvnBackend::newFrame();
    ImGui::NewFrame();

    for (Window *window : this->windows)
    {
        if (window->isEnabled())
            window->render();

        window->handleInputs();
    }

    ImGui::Render();
    ImguiNvnBackend::renderDrawData(ImGui::GetDrawData());
}