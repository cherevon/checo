/*
 * MIT License
 *
 * Copyright (c) 2026 Sergei Cherevichko
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

#include "checo/string.h"

#include <cstring>

namespace checo
{

String::String() noexcept
    : m_Data("\0", 1)
{
}

String::String(const char *cstr)
    : m_Data(cstr ? cstr : "\0", cstr ? std::strlen(cstr) + 1 : 1)
{
}

String::String(const std::string_view str)
    : m_Data('\0', str.size() + 1)
{
    std::copy_n(str.data(), str.size(), m_Data.data());
}

String::String(const String &other)
    : m_Data(other.m_Data)
{
}

String::String(String &&other) noexcept
    : m_Data(std::move(other.m_Data))
{
}

String::~String() noexcept = default;

bool String::operator>(const String &other) const noexcept
{
    const uint64_t minSize = m_Data.size() < other.m_Data.size() ? m_Data.size() : other.m_Data.size();
    const auto minSizeCmp = std::strncmp(m_Data.data(), other.m_Data.data(), minSize);
    if (minSizeCmp > 0) {
        return true;
    } else if (minSizeCmp < 0) {
        return false;
    }
    return m_Data.size() > other.m_Data.size();
}

bool String::operator<(const String &other) const noexcept
{
    const uint64_t minSize = m_Data.size() < other.m_Data.size() ? m_Data.size() : other.m_Data.size();
    const auto minSizeCmp = std::strncmp(m_Data.data(), other.m_Data.data(), minSize);
    if (minSizeCmp < 0) {
        return true;
    } else if (minSizeCmp > 0) {
        return false;
    }
    return m_Data.size() < other.m_Data.size();
}

} // namespace checo