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