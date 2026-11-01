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

#include "checo/log.h"

#include <vector>

namespace checo::log
{

struct WriterEntry
{
    LogWriter writer{nullptr};
    Level minLevel{Level::kTrace};
};

static std::vector<WriterEntry> m_Writers{};
static Level m_MinLevel{Level::kCritical};

void registerWriter(LogWriter writer, Level minLevel)
{
    if (writer) {
        m_Writers.push_back({writer, minLevel});
        if (minLevel < m_MinLevel) {
            m_MinLevel = minLevel;
        }
    }
}

void unregisterWriter(LogWriter writer)
{
    std::erase_if(m_Writers, [writer](const WriterEntry &entry) { return entry.writer == writer; });
}

bool isLevelEnabled(Level lvl)
{
    return lvl >= m_MinLevel;
}

void write(Level lvl, const char *file, int line, const char *message)
{
    for (const auto &entry : m_Writers) {
        if (lvl >= entry.minLevel && entry.writer) {
            entry.writer(lvl, file, line, message);
        }
    }
}

} // namespace checo::log
