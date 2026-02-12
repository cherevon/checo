#pragma once

#include "checo_logging_export.h"

#include <cstdint>
#include <string>

namespace checo::logging
{

/// Base class for logging. It provides a common interface for different logging implementations, such as logging to the
/// console, files, or remote servers. The log level can be set to filter out messages below a certain severity.
class CHECO_LOGGING_EXPORT Log
{
  public:
    enum class Level : uint8_t
    {
        Trace = 0,
        Info = 20,
        Warning = 40,
        Error = 60,
        Unknown = 255
    };

  public:
    Log();
    virtual ~Log();

  public:
    /// Set the log level. Messages with a level lower than the set level will be ignored.
    void setLevel(const Level level);

  public:
    /// Write a log message with the specified level. The message will be ignored if the level is lower than the set
    /// level.
    void write(const Level level, const std::string &message);

    void trace(const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
    void unknown(const std::string &message);

  protected:
    virtual void doWrite(const Level level, const std::string &message) = 0;

  private:
    Level m_Level{Level::Trace};
};

} // namespace checo::logging