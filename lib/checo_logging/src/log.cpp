#include "checo/logging/log.h"

namespace checo::logging
{

Log::Log() = default;

Log::~Log() = default;

void Log::setLevel(const Level level)
{
    m_Level = level;
}

void Log::write(const Level level, const std::string &message)
{
    // Dispatch the message to the child class to write the message.
    if (level >= m_Level)
    {
        doWrite(level, message);
    }
}

void Log::trace(const std::string &message)
{
    write(Level::Trace, message);
}

void Log::info(const std::string &message)
{
    write(Level::Info, message);
}

void Log::warning(const std::string &message)
{
    write(Level::Warning, message);
}

void Log::error(const std::string &message)
{
    write(Level::Error, message);
}

void Log::unknown(const std::string &message)
{
    write(Level::Unknown, message);
}

} // namespace checo::logging
