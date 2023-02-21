#include "button.hpp"
#include "starlight/ui.hpp"
#include "imgui.h"

Starlight::UI::Elements::Button::Button(std::string text, std::function<void()> onClick)
{
    this->text = text;
    this->onClick = onClick;
}

void Starlight::UI::Elements::Button::render()
{
    Starlight::UI::Utils::drawSeparator(42.5f, ImGui::GetCursorPosY(), ImGui::GetWindowWidth() - 85, 1, ImGui::GetColorU32(ImGuiCol_Separator));

    ImGui::SetWindowFontScale(1.25f);
    ImGui::SetCursorPosX(42.5f);
    if (ImGui::Button(this->text.c_str(), ImVec2(363, 69)))
    {
        if (this->onClick)
            this->onClick();
    }

    ImGui::SetWindowFontScale(1.0f);
}