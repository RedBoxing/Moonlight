#include "button.hpp"
#include "starlight/ui.hpp"
#include "imgui.h"

Starlight::UI::Button::Button(std::string text, std::function<void()> onClick)
{
    this->text = text;
    this->onClick = onClick;
}

void Starlight::UI::Button::render()
{
    Starlight::UI::Utils::drawSeparator(32, ImGui::GetCursorPosY(), ImGui::GetWindowWidth() - 85, 1, ImGui::GetColorU32(ImGuiCol_Border));

    ImGui::SetCursorPosX(32);
    if (ImGui::Button(this->text.c_str()))
    {
        if (this->onClick)
            this->onClick();
    }
}