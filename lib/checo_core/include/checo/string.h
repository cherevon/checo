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

#pragma once

#include "checo/byte_array.h"
#include "checo_core_export.h"

#include <string_view>

namespace checo
{

class CHECO_CORE_EXPORT String final
{
  public:
    String() noexcept;
    String(const char *cstr);
    String(const std::string_view str);

    String(const String &other);
    String(String &&other) noexcept;

    ~String() noexcept;

  public:
    String &operator=(const String &other);
    String &operator=(String &&other) noexcept;

    bool operator==(const String &other) const noexcept;
    bool operator>(const String &other) const noexcept;
    bool operator<(const String &other) const noexcept;
    bool operator<=(const String &other) const noexcept;
    bool operator>=(const String &other) const noexcept;

    operator std::string_view() const noexcept;

  public:
    size_t size() const noexcept;

    char *data() noexcept;
    const char *data() const noexcept;

    void clear();

  private:
    ByteArray m_Data{};
};

inline String &String::operator=(const String &other)
{
    if (this == &other) {
        return *this;
    }

    m_Data = other.m_Data;
    return *this;
}

inline String &String::operator=(String &&other) noexcept
{
    if (this == &other) {
        return *this;
    }

    m_Data = std::move(other.m_Data);
    return *this;
}

inline bool String::operator==(const String &other) const noexcept
{
    return m_Data == other.m_Data;
}

inline bool String::operator>(const String &other) const noexcept
{
    return std::string_view(*this) > std::string_view(other);
}

inline bool String::operator<(const String &other) const noexcept
{
    return std::string_view(*this) < std::string_view(other);
}

inline bool String::operator<=(const String &other) const noexcept
{
    return !(*this > other);
}

inline bool String::operator>=(const String &other) const noexcept
{
    return !(*this < other);
}

inline String::operator std::string_view() const noexcept
{
    return std::string_view(m_Data.data(), m_Data.size() - 1);
}

inline size_t String::size() const noexcept
{
    return m_Data.size() - 1;
}

inline char *String::data() noexcept
{
    return m_Data.data();
}

inline const char *String::data() const noexcept
{
    return m_Data.data();
}

inline void String::clear()
{
    m_Data.setData("\0", 1);
}

} // namespace checo