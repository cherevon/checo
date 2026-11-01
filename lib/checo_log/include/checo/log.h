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

namespace checo::log
{

enum class Level : uint8_t {
    kTrace = 0,
    kDebug = 20,
    kInfo = 40,
    kWarning = 60,
    kError = 80,
    kCritical = 100,
};

using LogWriter = void (*)(Level lvl, const char *file, int line, const char *message);

CHECO_LOG_EXPORT void registerWriter(LogWriter writer, Level minLevel);
CHECO_LOG_EXPORT void unregisterWriter(LogWriter writer);

CHECO_LOG_EXPORT bool isLevelEnabled(Level lvl);
CHECO_LOG_EXPORT void write(Level lvl, const char *file, int line, const char *message);

template <typename... Args>
void write(Level lvl, const char *file, int line, std::format_string<Args...> fmt, Args &&...args)
{
    if (isLevelEnabled(lvl)) {
        write(lvl, file, line, std::format(fmt, std::forward<Args>(args)...).c_str());
    }
}

} // namespace checo::log

#define LOG_TRACE(...) checo::log::write(checo::log::Level::kTrace, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) checo::log::write(checo::log::Level::kDebug, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) checo::log::write(checo::log::Level::kInfo, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) checo::log::write(checo::log::Level::kWarning, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) checo::log::write(checo::log::Level::kError, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_CRITICAL(...) checo::log::write(checo::log::Level::kCritical, __FILE__, __LINE__, __VA_ARGS__)