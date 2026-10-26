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

#include "checo/byte_array.h"

#include <cstring>
#include <utility>

namespace checo
{

ByteArray::ByteArray() noexcept
    : m_Metadata{.m_DataSize = 0, .m_IsOnHeap = false}
{
}

ByteArray::ByteArray(const char fillChar, size_t dataSize)
    : m_Metadata{.m_DataSize = 0, .m_IsOnHeap = false}
{
    if (dataSize == 0) {
        return;
    }

    m_Metadata.m_DataSize = dataSize;
    m_Metadata.m_IsOnHeap = dataSize > MAX_STACK_DATA_SIZE;
    if (m_Metadata.m_IsOnHeap) {
        m_HeapData.m_Data = new char[m_Metadata.m_DataSize];
        std::memset(m_HeapData.m_Data, fillChar, m_Metadata.m_DataSize);
    } else {
        std::memset(m_StackData, fillChar, m_Metadata.m_DataSize);
    }
}

ByteArray::ByteArray(const char *data, size_t dataSize)
{
    setData(data, dataSize);
}

ByteArray::ByteArray(const ByteArray &other)
{
    // Nothing to do if copying from self
    if (this == &other) {
        return;
    }

    // Copy data
    setData(other.data(), other.size());
}

ByteArray::ByteArray(ByteArray &&other) noexcept
{
    // Nothing to do if moving from self
    if (this == &other) {
        return;
    }

    // Move new data from other
    m_Metadata = std::move(other.m_Metadata);
    if (m_Metadata.m_IsOnHeap) {
        m_HeapData.m_Data = other.m_HeapData.m_Data;
        other.m_HeapData.m_Data = nullptr;
        other.m_Metadata.m_IsOnHeap = false;
    } else {
        std::memcpy(m_StackData, other.m_StackData, other.m_Metadata.m_DataSize);
    }
}

ByteArray::~ByteArray() noexcept
{
    clear();
}

ByteArray &ByteArray::operator=(const ByteArray &other)
{
    // Nothing to do if assigning from self
    if (this == &other) {
        return *this;
    }

    // Clear old data
    clear();

    // Copy new data from other
    setData(other.data(), other.size());

    // Success
    return *this;
}

ByteArray &ByteArray::operator=(ByteArray &&other) noexcept
{
    // Nothing to do if assigning from self
    if (this == &other) {
        return *this;
    }

    // Clear old data
    clear();

    // Move new data from other
    m_Metadata = std::move(other.m_Metadata);
    if (m_Metadata.m_IsOnHeap) {
        m_HeapData.m_Data = other.m_HeapData.m_Data;
        other.m_HeapData.m_Data = nullptr;
        other.m_Metadata.m_IsOnHeap = false;
    } else {
        std::memcpy(m_StackData, other.m_StackData, other.m_Metadata.m_DataSize);
    }

    // Success
    return *this;
}

bool ByteArray::operator==(const ByteArray &other) const noexcept
{
    if (m_Metadata.m_IsOnHeap != other.m_Metadata.m_IsOnHeap || m_Metadata.m_DataSize != other.m_Metadata.m_DataSize) {
        return false;
    }

    if (m_Metadata.m_IsOnHeap) {
        return std::memcmp(m_HeapData.m_Data, other.m_HeapData.m_Data, m_Metadata.m_DataSize) == 0;
    } else {
        return std::memcmp(m_StackData, other.m_StackData, m_Metadata.m_DataSize) == 0;
    }
}

void ByteArray::setData(const char *data, size_t dataSize)
{
    // Clear old data
    clear();

    // Nothing to do if the data pointer is null
    if (!data) {
        return;
    }

    // Set new data
    m_Metadata.m_DataSize = dataSize;
    m_Metadata.m_IsOnHeap = dataSize > MAX_STACK_DATA_SIZE;
    if (m_Metadata.m_IsOnHeap) {
        m_HeapData.m_Data = new char[m_Metadata.m_DataSize];
        std::memcpy(m_HeapData.m_Data, data, m_Metadata.m_DataSize);
    } else {
        std::memcpy(m_StackData, data, m_Metadata.m_DataSize);
    }
}

void ByteArray::clear() noexcept
{
    if (m_Metadata.m_IsOnHeap && m_HeapData.m_Data) {
        delete[] m_HeapData.m_Data;
        m_HeapData.m_Data = nullptr;
    }
    m_Metadata.m_DataSize = 0;
    m_Metadata.m_IsOnHeap = false;
}

} // namespace checo