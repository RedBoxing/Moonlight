#include "console_window.hpp"
#include "imgui.h"
#include "logger.hpp"

Moonlight::UI::Elements::Console *consoleInstance;

Moonlight::UI::Windows::ConsoleWindow::ConsoleWindow() : Starlight::UI::Window("Moonlight Console", 1280 - 448, 0, 448, 720, true)
{
    this->addElement(new Moonlight::UI::Elements::Console());
}

Moonlight::UI::Elements::Console::Console()
{
    consoleInstance = this;
    Moonlight::Logger::addListener([](const char *line)
                                   { consoleInstance->loggerCallback(line); });
}

void Moonlight::UI::Elements::Console::loggerCallback(const char *line)
{
    this->history.push_back(line);

    if (this->history.size() > 50)
    {
        // remove the 25 oldest lines
        this->history.erase(this->history.begin(), this->history.begin() + 25);
    }
}

void Moonlight::UI::Elements::Console::render()
{

    //  if (ImGui::BeginChild("ScrollRegion##", ImVec2(0, -(ImGui::GetFrameHeightWithSpacing() + 10)), false, 0))
    //{
    ImGui::PushTextWrapPos();

    for (const auto &line : this->history)
    {
        ImGui::TextWrapped(line.c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::PopTextWrapPos();
    // }
}
