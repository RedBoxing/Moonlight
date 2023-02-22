#pragma once

#include "../types.h"

namespace nn
{
    namespace settings
    {
        namespace factory
        {
            struct SerialNumber
            {
                char serialNumber[0x18];
            };
        }

        namespace system
        {
            struct SerialNumber
            {
                char serialNumber[0x18];
            };
        }

        namespace detail
        {
            void GetSerialNumber(factory::SerialNumber *serialNumber);
            void GetSerialNumber(system::SerialNumber *serialNumber);
        }
    }
}