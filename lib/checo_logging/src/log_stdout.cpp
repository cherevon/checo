#include "checo/logging/log_stdout.h"

#include <chrono>
#include <format>
#include <iostream>

namespace checo::logging
{

static constexpr const char *FMT_MESSAGE = "[{}][{}]: {}";

inline std::string formatLogMessage(const std::string &level, const std::string &message)
{
    return std::format(FMT_MESSAGE, std::chrono::system_clock::now(), level, message);
}

LogStdOut::LogStdOut() = default;

LogStdOut::~LogStdOut() = default;

void LogStdOut::doWrite(const Level level, const std::string &message)
{
    switch (level)
    {
    case Level::Trace:
        std::cout << formatLogMessage("TRACE", message) << std::endl;
        break;
    case Level::Info:
        std::cout << formatLogMessage("INFO", message) << std::endl;
        break;
    case Level::Warning:
        std::cout << formatLogMessage("WARNING", message) << std::endl;
        break;
    case Level::Error:
        std::cerr << formatLogMessage("ERROR", message) << std::endl;
        break;
    case Level::Unknown:
        std::cout << formatLogMessage("UNKNOWN", message) << std::endl;
        break;
    }
}

} // namespace checo::logging