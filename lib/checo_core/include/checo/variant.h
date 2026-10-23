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

#include <cstdint>

namespace checo
{

class CHECO_CORE_EXPORT Variant final
{
  public:
    enum class Type : uint8_t {
        Empty = 0,
        Bool,
        Int32,
        Int64,
        UnsignedInt32,
        UnsignedInt64,
        Float,
        Double,
        ByteArray,
    };

  public:
    Variant() noexcept;
    Variant(const bool value);
    Variant(const int32_t value);
    Variant(const int64_t value);
    Variant(const uint32_t value);
    Variant(const uint64_t value);
    Variant(const float value);
    Variant(const double value);
    Variant(const ByteArray &value);

    Variant(const Variant &);
    Variant(Variant &&) noexcept;

    ~Variant();

  public:
    Variant &operator=(const Variant &);
    Variant &operator=(Variant &&) noexcept;

    Variant &operator=(const bool value);
    Variant &operator=(const int32_t value);
    Variant &operator=(const int64_t value);
    Variant &operator=(const uint32_t value);
    Variant &operator=(const uint64_t value);
    Variant &operator=(const float value);
    Variant &operator=(const double value);
    Variant &operator=(const ByteArray &value);
    Variant &operator=(ByteArray &&value);

    bool operator==(const Variant &) const noexcept;

    inline bool operator==(const bool value) const noexcept { return isBool() && m_Bool == value; }

    inline bool operator==(const int32_t value) const noexcept { return isInt32() && m_Int32 == value; }

    inline bool operator==(const int64_t value) const noexcept { return isInt64() && m_Int64 == value; }

    inline bool operator==(const uint32_t value) const noexcept
    {
        return isUnsignedInt32() && m_UnsignedInt32 == value;
    }

    inline bool operator==(const uint64_t value) const noexcept
    {
        return isUnsignedInt64() && m_UnsignedInt64 == value;
    }

    inline bool operator==(const float value) const noexcept { return isFloat() && m_Float == value; }

    inline bool operator==(const double value) const noexcept { return isDouble() && m_Double == value; }

    inline bool operator==(const ByteArray &value) const noexcept { return isByteArray() && m_ByteArray == value; }

  public:
    inline Type getType() const noexcept { return m_Type; }

    inline bool isEmpty() const noexcept { return m_Type == Type::Empty; }

    inline bool isBool() const noexcept { return m_Type == Type::Bool; }

    inline bool isInt32() const noexcept { return m_Type == Type::Int32; }

    inline bool isInt64() const noexcept { return m_Type == Type::Int64; }

    inline bool isUnsignedInt32() const noexcept { return m_Type == Type::UnsignedInt32; }

    inline bool isUnsignedInt64() const noexcept { return m_Type == Type::UnsignedInt64; }

    inline bool isFloat() const noexcept { return m_Type == Type::Float; }

    inline bool isDouble() const noexcept { return m_Type == Type::Double; }

    inline bool isByteArray() const noexcept { return m_Type == Type::ByteArray; }

    inline bool getBool() const noexcept { return m_Bool; }

    inline int32_t getInt32() const noexcept { return m_Int32; }

    inline int64_t getInt64() const noexcept { return m_Int64; }

    inline uint32_t getUnsignedInt32() const noexcept { return m_UnsignedInt32; }

    inline uint64_t getUnsignedInt64() const noexcept { return m_UnsignedInt64; }

    inline float getFloat() const noexcept { return m_Float; }

    inline double getDouble() const noexcept { return m_Double; }

    const ByteArray &getByteArray() const noexcept;

    void clear() noexcept;

  private:
    Type m_Type{Type::Empty};

    union
    {
        bool m_Bool;
        int32_t m_Int32;
        int64_t m_Int64;
        uint32_t m_UnsignedInt32;
        uint64_t m_UnsignedInt64;
        float m_Float;
        double m_Double;
        ByteArray m_ByteArray;
    };
};

} // namespace checo