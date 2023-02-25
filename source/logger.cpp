#include "logger.hpp"
#include "nn/util.h"

static Moonlight::Logger logger;

Moonlight::Logger &Moonlight::Logger::instance()
{
    return logger;
}

void Moonlight::Logger::log(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Moonlight::Logger::log(fmt, args);
    va_end(args);
}

void Moonlight::Logger::log(const char *fmt, va_list args)
{
    char buffer[0x1000] = {};
    if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0)
    {
        for (auto listener : instance().listeners)
        {
            (*listener)(buffer);
        }
    }
}

void Moonlight::Logger::addListener(LogCallback callback)
{
    Moonlight::Logger::instance().listeners.push_back(callback);
}