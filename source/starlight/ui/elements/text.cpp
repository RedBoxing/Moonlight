#include "text.hpp"
#include "starlight/ui.hpp"
#include "imgui.h"

Starlight::UI::Elements::Text::Text(std::string text)
{
    this->text = text;
}

void Starlight::UI::Elements::Text::render()
{
    ImGui::SetWindowFontScale(0.5f);
    ImGui::Text(this->text.c_str());
    ImGui::SetWindowFontScale(1.0f);
}