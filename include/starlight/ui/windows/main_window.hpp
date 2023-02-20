#pragma once

#include "window.hpp"

namespace Starlight
{
    namespace UI
    {
        namespace Windows
        {
            class MainWindow : public Window
            {
            public:
                MainWindow();
                ~MainWindow();

                void handleInputs();
            };
        }
    }
}