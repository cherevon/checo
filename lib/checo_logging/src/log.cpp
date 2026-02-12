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
