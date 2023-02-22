#pragma once

#include "starlight.hpp"

namespace Moonlight
{
    namespace UI
    {
        class Overlay : public Starlight::UI::Overlay
        {
        public:
            Overlay();
        };

        inline Moonlight::UI::Overlay *g_overlay = nullptr;
    }
}