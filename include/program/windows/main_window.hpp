#pragma once

#include "starlight.hpp"

namespace Moonlight
{
    namespace UI
    {
        namespace Windows
        {
            class MainWindow : public Starlight::UI::Window
            {
            public:
                MainWindow();
                ~MainWindow();

                void handleInputs() override;
                void onEnable() override;
                void onDisable() override;
            };
        }
    }
}