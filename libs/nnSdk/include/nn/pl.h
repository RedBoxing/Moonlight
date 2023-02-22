#pragma once

#include "settings.h"
#include "result.h"
#include "../types.h"

namespace nn
{
    namespace pl
    {
        enum SharedFontType
        {
            SharedFontType_Standard = 0,
            SharedFontType_ChineseSimplified = 1,
            SharedFontType_ExtChineseSimplified = 2,
            SharedFontType_ChineseTraditional = 3,
            SharedFontType_Korean = 4,
            SharedFontType_NintendoExt = 5,
        };

        struct SharedFontData
        {
        };

        u32 GetSharedFontLoadState(SharedFontType fontType);
        u64 GetSharedFontAddress(SharedFontType fontType);
        u32 GetSharedFontSize(SharedFontType fontType);
        // nn::Result GetSharedFont(int *, SharedFontData *data, nn::settings::LanguageCode code);
        void RequestSharedFontLoad(SharedFontType fontType);
    }
}