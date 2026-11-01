/*
 * MIT License
 *
 * Copyright (c) 2024 Sergei Cherevichko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "checo_log_export.h"

#include <cstdint>
#include <format>
#include <string_view>
#include <utility>

namespace checo::log
{

/// Base class for logging. It provides a common interface for different logging implementations, such as logging to the
/// console, files, or remote servers. The log level can be set to filter out messages below a certain severity.
class CHECO_LOG_EXPORT Log
{
  public:
    enum class Level : uint8_t {
        kTrace = 0,
        kDebug = 20,
        kInfo = 40,
        kWarning = 60,
        kError = 80,
        kCritical = 100,
    };

  public:
    static constexpr const char *levelToString(Level lvl) noexcept;

  public:
    explicit Log(Level lvl = Level::kTrace) noexcept;
    virtual ~Log();

  public:
    /// Set the log level. Messages with a level lower than the set level will be ignored
    void setLevel(Level lvl);

  public:
    /// Write a log message with the specified level. The message will be ignored if the level is lower than the set
    /// level
    virtual void write(Level lvl, std::string_view message);
    template <typename... Args>
    void write(Level lvl, std::format_string<Args...> format, Args &&...args);

    void trace(std::string_view message);
    template <typename... Args>
    void trace(std::format_string<Args...> format, Args &&...args);

    void debug(std::string_view message);
    template <typename... Args>
    void debug(std::format_string<Args...> format, Args &&...args);

    void info(std::string_view message);
    template <typename... Args>
    void info(std::format_string<Args...> format, Args &&...args);

    void warning(std::string_view message);
    template <typename... Args>
    void warning(std::format_string<Args...> format, Args &&...args);

    void error(std::string_view message);
    template <typename... Args>
    void error(std::format_string<Args...> format, Args &&...args);

    void critical(std::string_view message);
    template <typename... Args>
    void critical(std::format_string<Args...> format, Args &&...args);

  protected:
    virtual void doWrite(Level lvl, std::string_view message) = 0;

  private:
    Level m_Level{Level::kTrace};
};

template <typename... Args>
void logTrace(checo::log::Log *log, std::format_string<Args...> format, Args &&...args)
{
    if (log) {
        log->trace(format, std::forward<Args>(args)...);
    }
}

template <typename... Args>
void logDebug(checo::log::Log *log, std::format_string<Args...> format, Args &&...args)
{
    if (log) {
        log->debug(format, std::forward<Args>(args)...);
    }
}

template <typename... Args>
void logInfo(checo::log::Log *log, std::format_string<Args...> format, Args &&...args)
{
    if (log) {
        log->info(format, std::forward<Args>(args)...);
    }
}

template <typename... Args>
void logWarning(checo::log::Log *log, std::format_string<Args...> format, Args &&...args)
{
    if (log) {
        log->warning(format, std::forward<Args>(args)...);
    }
}

template <typename... Args>
void logError(checo::log::Log *log, std::format_string<Args...> format, Args &&...args)
{
    if (log) {
        log->error(format, std::forward<Args>(args)...);
    }
}

template <typename... Args>
void logCritical(checo::log::Log *log, std::format_string<Args...> format, Args &&...args)
{
    if (log) {
        log->critical(format, std::forward<Args>(args)...);
    }
}

inline constexpr const char *Log::levelToString(Level lvl) noexcept
{
    switch (lvl) {
    case Level::kTrace:
        return "TRACE";
    case Level::kDebug:
        return "DEBUG";
    case Level::kInfo:
        return "INFO";
    case Level::kWarning:
        return "WARNING";
    case Level::kError:
        return "ERROR";
    case Level::kCritical:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}

inline void Log::setLevel(Level lvl)
{
    m_Level = lvl;
}

inline void Log::write(Level lvl, std::string_view message)
{
    if (lvl >= m_Level) {
        doWrite(lvl, message);
    }
}

template <typename... Args>
inline void Log::write(Level lvl, std::format_string<Args...> format, Args &&...args)
{
    write(lvl, std::format(format, std::forward<Args>(args)...));
}

inline void Log::trace(std::string_view message)
{
    write(Level::kTrace, message);
}

template <typename... Args>
inline void Log::trace(std::format_string<Args...> format, Args &&...args)
{
    write(Level::kTrace, format, std::forward<Args>(args)...);
}

inline void Log::debug(std::string_view message)
{
    write(Level::kDebug, message);
}

template <typename... Args>
inline void Log::debug(std::format_string<Args...> format, Args &&...args)
{
    write(Level::kDebug, format, std::forward<Args>(args)...);
}

inline void Log::info(std::string_view message)
{
    write(Level::kInfo, message);
}

template <typename... Args>
inline void Log::info(std::format_string<Args...> format, Args &&...args)
{
    write(Level::kInfo, format, std::forward<Args>(args)...);
}

inline void Log::warning(std::string_view message)
{
    write(Level::kWarning, message);
}

template <typename... Args>
inline void Log::warning(std::format_string<Args...> format, Args &&...args)
{
    write(Level::kWarning, format, std::forward<Args>(args)...);
}

inline void Log::error(std::string_view message)
{
    write(Level::kError, message);
}

template <typename... Args>
inline void Log::error(std::format_string<Args...> format, Args &&...args)
{
    write(Level::kError, format, std::forward<Args>(args)...);
}

inline void Log::critical(std::string_view message)
{
    write(Level::kCritical, message);
}

template <typename... Args>
inline void Log::critical(std::format_string<Args...> format, Args &&...args)
{
    write(Level::kCritical, format, std::forward<Args>(args)...);
}

} // namespace checo::log