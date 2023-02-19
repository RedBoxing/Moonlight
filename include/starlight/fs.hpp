#pragma once

#include "nn/result.h"

namespace Starlight
{
    namespace FS
    {
        struct LoadData
        {
            const char *path;
            int alignment = 8;
            void *buffer;
            long bufSize;
        };

        bool doesFileExist(const char *path);
        nn::Result writeFile(const char *path, const void *data, size_t size);
        void readFile(const char *path, void **data, size_t *size);
        void loadFile(LoadData &loadData);
    }
}