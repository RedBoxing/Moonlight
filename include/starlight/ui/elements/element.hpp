#pragma once

namespace Starlight
{
    namespace UI
    {
        class Element
        {
        public:
            Element();
            virtual ~Element();

            virtual void render();
        };
    }
}