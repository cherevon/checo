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