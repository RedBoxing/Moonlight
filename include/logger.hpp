#pragma once

#include <functional>
#include <cstdarg>

typedef void (*LogCallback)(const char *);

namespace Moonlight
{
    class Logger
    {
    public:
        Logger() = default;

        static void log(const char *fmt, ...);
        static void log(const char *fmt, va_list args);
        static void addListener(LogCallback callback);

    private:
        std::vector<LogCallback> listeners;
        static Logger &instance();
    };
}