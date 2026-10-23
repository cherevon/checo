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

#include "checo/variant.h"

#include <utility>

namespace checo
{

Variant::Variant() noexcept = default;

Variant::Variant(const bool value)
    : m_Type(Variant::Type::Bool),
      m_Bool(value)
{
}

Variant::Variant(const int32_t value)
    : m_Type(Variant::Type::Int32),
      m_Int32(value)
{
}

Variant::Variant(const int64_t value)
    : m_Type(Variant::Type::Int64),
      m_Int64(value)
{
}

Variant::Variant(const uint32_t value)
    : m_Type(Variant::Type::UnsignedInt32),
      m_UnsignedInt32(value)
{
}

Variant::Variant(const uint64_t value)
    : m_Type(Variant::Type::UnsignedInt64),
      m_UnsignedInt64(value)
{
}

Variant::Variant(const float value)
    : m_Type(Variant::Type::Float),
      m_Float(value)
{
}

Variant::Variant(const double value)
    : m_Type(Variant::Type::Double),
      m_Double(value)
{
}

Variant::Variant(const ByteArray &value)
    : m_Type(Variant::Type::ByteArray)
{
    ::new (&m_ByteArray) ByteArray(value);
}

Variant::Variant(const Variant &other)
    : m_Type(other.m_Type)
{
    switch (m_Type) {
    case Variant::Type::Bool:
        m_Bool = other.m_Bool;
        break;
    case Variant::Type::Int32:
        m_Int32 = other.m_Int32;
        break;
    case Variant::Type::Int64:
        m_Int64 = other.m_Int64;
        break;
    case Variant::Type::UnsignedInt32:
        m_UnsignedInt32 = other.m_UnsignedInt32;
        break;
    case Variant::Type::UnsignedInt64:
        m_UnsignedInt64 = other.m_UnsignedInt64;
        break;
    case Variant::Type::Float:
        m_Float = other.m_Float;
        break;
    case Variant::Type::Double:
        m_Double = other.m_Double;
        break;
    case Variant::Type::ByteArray:
        ::new (&m_ByteArray) ByteArray(other.m_ByteArray);
        break;
    case Variant::Type::Empty:
    default:
        // Unknown type, do nothing
        break;
    }
}

Variant::Variant(Variant &&other) noexcept
    : m_Type(other.m_Type)
{
    switch (m_Type) {
    case Variant::Type::Bool:
        m_Bool = other.m_Bool;
        break;
    case Variant::Type::Int32:
        m_Int32 = other.m_Int32;
        break;
    case Variant::Type::Int64:
        m_Int64 = other.m_Int64;
        break;
    case Variant::Type::UnsignedInt32:
        m_UnsignedInt32 = other.m_UnsignedInt32;
        break;
    case Variant::Type::UnsignedInt64:
        m_UnsignedInt64 = other.m_UnsignedInt64;
        break;
    case Variant::Type::Float:
        m_Float = other.m_Float;
        break;
    case Variant::Type::Double:
        m_Double = other.m_Double;
        break;
    case Variant::Type::ByteArray:
        ::new (&m_ByteArray) ByteArray(std::move(other.m_ByteArray));
        other.m_Type = Variant::Type::Empty;
        break;
    case Variant::Type::Empty:
    default:
        // Unknown type, do nothing
        break;
    }
}

Variant::~Variant()
{
    clear();
}

Variant &Variant::operator=(const Variant &other)
{
    if (this == &other) {
        return *this;
    }

    // Clear old data
    if (m_Type != other.m_Type) {
        clear();
    }

    // Copy new data
    switch (m_Type) {
    case Variant::Type::Bool:
        m_Bool = other.m_Bool;
        break;
    case Variant::Type::Int32:
        m_Int32 = other.m_Int32;
        break;
    case Variant::Type::Int64:
        m_Int64 = other.m_Int64;
        break;
    case Variant::Type::UnsignedInt32:
        m_UnsignedInt32 = other.m_UnsignedInt32;
        break;
    case Variant::Type::UnsignedInt64:
        m_UnsignedInt64 = other.m_UnsignedInt64;
        break;
    case Variant::Type::Float:
        m_Float = other.m_Float;
        break;
    case Variant::Type::Double:
        m_Double = other.m_Double;
        break;
    case Variant::Type::ByteArray:
        if (m_Type == Variant::Type::ByteArray) {
            m_ByteArray = other.m_ByteArray;
        } else {
            ::new (&m_ByteArray) ByteArray(other.m_ByteArray);
        }
        break;
    case Variant::Type::Empty:
    default:
        // Unknown type, do nothing
        break;
    }
    m_Type = other.m_Type;

    // Success
    return *this;
}

Variant &Variant::operator=(Variant &&other) noexcept
{
    if (this == &other) {
        return *this;
    }

    // Clear old data
    if (m_Type != other.m_Type) {
        clear();
    }

    // Move new data
    switch (m_Type) {
    case Variant::Type::Bool:
        m_Bool = other.m_Bool;
        break;
    case Variant::Type::Int32:
        m_Int32 = other.m_Int32;
        break;
    case Variant::Type::Int64:
        m_Int64 = other.m_Int64;
        break;
    case Variant::Type::UnsignedInt32:
        m_UnsignedInt32 = other.m_UnsignedInt32;
        break;
    case Variant::Type::UnsignedInt64:
        m_UnsignedInt64 = other.m_UnsignedInt64;
        break;
    case Variant::Type::Float:
        m_Float = other.m_Float;
        break;
    case Variant::Type::Double:
        m_Double = other.m_Double;
        break;
    case Variant::Type::ByteArray:
        if (m_Type == Variant::Type::ByteArray) {
            m_ByteArray = std::move(other.m_ByteArray);
        } else {
            ::new (&m_ByteArray) ByteArray(std::move(other.m_ByteArray));
        }
        break;
    case Variant::Type::Empty:
    default:
        // Unknown type, do nothing
        break;
    }
    m_Type = other.m_Type;

    // Success
    return *this;
}

Variant &Variant::operator=(const bool value)
{
    clear();

    m_Type = Variant::Type::Bool;
    m_Bool = value;

    return *this;
}

Variant &Variant::operator=(const int32_t value)
{
    clear();

    m_Type = Variant::Type::Int32;
    m_Int32 = value;

    return *this;
}

Variant &Variant::operator=(const int64_t value)
{
    clear();

    m_Type = Variant::Type::Int64;
    m_Int64 = value;

    return *this;
}

Variant &Variant::operator=(const uint32_t value)
{
    clear();

    m_Type = Variant::Type::UnsignedInt32;
    m_UnsignedInt32 = value;

    return *this;
}

Variant &Variant::operator=(const uint64_t value)
{
    clear();

    m_Type = Variant::Type::UnsignedInt64;
    m_UnsignedInt64 = value;

    return *this;
}

Variant &Variant::operator=(const float value)
{
    clear();

    m_Type = Variant::Type::Float;
    m_Float = value;

    return *this;
}

Variant &Variant::operator=(const double value)
{
    clear();

    m_Type = Variant::Type::Double;
    m_Double = value;

    return *this;
}

Variant &Variant::operator=(const ByteArray &value)
{
    if (m_Type == Variant::Type::ByteArray) {
        m_ByteArray = value;
    } else {
        clear();

        ::new (&m_ByteArray) ByteArray(value);
        m_Type = Variant::Type::ByteArray;
    }

    return *this;
}

Variant &Variant::operator=(ByteArray &&value)
{
    if (m_Type == Variant::Type::ByteArray) {
        m_ByteArray = std::move(value);
    } else {
        clear();

        ::new (&m_ByteArray) ByteArray(std::move(value));
        m_Type = Variant::Type::ByteArray;
    }

    return *this;
}

bool Variant::operator==(const Variant &other) const noexcept
{
    if (m_Type != other.m_Type) {
        return false;
    }

    switch (m_Type) {
    case Variant::Type::Bool:
        return m_Bool == other.m_Bool;
    case Variant::Type::Int32:
        return m_Int32 == other.m_Int32;
    case Variant::Type::Int64:
        return m_Int64 == other.m_Int64;
    case Variant::Type::UnsignedInt32:
        return m_UnsignedInt32 == other.m_UnsignedInt32;
    case Variant::Type::UnsignedInt64:
        return m_UnsignedInt64 == other.m_UnsignedInt64;
    case Variant::Type::Float:
        return m_Float == other.m_Float;
    case Variant::Type::Double:
        return m_Double == other.m_Double;
    case Variant::Type::ByteArray:
        return m_ByteArray == other.m_ByteArray;
    case Variant::Type::Empty:
    default:
        return true;
    }
}

const ByteArray &Variant::getByteArray() const noexcept
{
    if (m_Type != Variant::Type::ByteArray) {
        static const ByteArray empty;
        return empty;
    }

    return m_ByteArray;
}

void Variant::clear() noexcept
{
    if (m_Type == Variant::Type::ByteArray) {
        m_ByteArray.~ByteArray();
    }
    m_Type = Variant::Type::Empty;
}

} // namespace checo