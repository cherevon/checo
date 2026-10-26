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

#include "checo_core_export.h"

namespace checo
{

class CHECO_CORE_EXPORT ByteArray final
{
  public:
    ByteArray() noexcept;
    ByteArray(const char fillChar, size_t dataSize);
    ByteArray(const char *data, size_t dataSize);

    ByteArray(const ByteArray &other);
    ByteArray(ByteArray &&other) noexcept;

    ~ByteArray() noexcept;

  public:
    ByteArray &operator=(const ByteArray &other);
    ByteArray &operator=(ByteArray &&other) noexcept;

    bool operator==(const ByteArray &other) const noexcept;

  public:
    size_t size() const noexcept;

    char *data() noexcept;
    const char *data() const noexcept;
    void setData(const char *data, size_t dataSize);

    void clear() noexcept;

  private:
    struct HeapData
    {
        char *m_Data{nullptr};
    };

    static constexpr size_t MAX_STACK_DATA_SIZE{sizeof(HeapData)};

    struct
    {
        size_t m_DataSize : (sizeof(size_t) * 8 - 1) = 0;
        bool m_IsOnHeap   : 1 = false;
    } m_Metadata;

    union
    {
        HeapData m_HeapData;
        char m_StackData[MAX_STACK_DATA_SIZE];
    };
};

inline size_t ByteArray::size() const noexcept
{
    return m_Metadata.m_DataSize;
}

inline char *ByteArray::data() noexcept
{
    return m_Metadata.m_IsOnHeap ? m_HeapData.m_Data : m_StackData;
}

inline const char *ByteArray::data() const noexcept
{
    return m_Metadata.m_IsOnHeap ? m_HeapData.m_Data : m_StackData;
}

} // namespace checo