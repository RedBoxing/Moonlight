#include "menu.hpp"
#include "starlight/hid.hpp"
#include "windows/main_window.hpp"
#include "windows/notifications_window.hpp"
#include "starlight/ui.hpp"

#include "imgui/imgui_impl_nvn.hpp"

Starlight::UI::Windows::NotificationsWindow *notificationsWindow = nullptr;

Starlight::UI::Menu::Menu() {}

bool focus = false;

void Starlight::UI::Menu::Initialize()
{
    this->windows.push_back(new Windows::MainWindow());

    notificationsWindow = new Windows::NotificationsWindow();
    this->windows.push_back(notificationsWindow);
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

bool Starlight::UI::Menu::isFocused()
{
    return focus;
}

void Starlight::UI::Menu::setFocused(bool focused)
{
    focus = focused;
}

void Starlight::UI::displayNotification(std::string text, nn::TimeSpan duration)
{
    notificationsWindow->addNotification(Notification(text, duration));
}