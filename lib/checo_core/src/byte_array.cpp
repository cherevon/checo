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

namespace checo
{

ByteArray::ByteArray() noexcept = default;

ByteArray::ByteArray(const char *data, uint64_t dataSize)
    : m_IsSmall(dataSize <= MAX_SMALL_DATA_SIZE)
{
    m_DataSize = dataSize;
    if (m_IsSmall) {
        std::memcpy(m_SmallData, data, dataSize);
    } else {
        m_LargeData = new char[dataSize];
        std::memcpy(m_LargeData, data, dataSize);
    }
}

ByteArray::ByteArray(const ByteArray &other)
{
    // Nothing to do if copying from self
    if (this == &other) {
        return;
    }

    // Clear old data
    clear();

    // Copy new data from other
    m_IsSmall = other.m_IsSmall;
    m_DataSize = other.m_DataSize;
    if (m_IsSmall) {
        std::memcpy(m_SmallData, other.m_SmallData, other.m_DataSize);
    } else {
        m_LargeData = new char[other.m_DataSize];
        std::memcpy(m_LargeData, other.m_LargeData, other.m_DataSize);
    }
}

ByteArray::ByteArray(ByteArray &&other) noexcept
{
    // Nothing to do if moving from self
    if (this == &other) {
        return;
    }

    // Clear old data
    clear();

    // Move new data from other
    m_IsSmall = other.m_IsSmall;
    m_DataSize = other.m_DataSize;
    if (m_IsSmall) {
        std::memcpy(m_SmallData, other.m_SmallData, other.m_DataSize);
    } else {
        m_LargeData = other.m_LargeData;
        other.m_LargeData = nullptr;
        other.m_DataSize = 0;
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
    m_IsSmall = other.m_IsSmall;
    m_DataSize = other.m_DataSize;
    if (m_IsSmall) {
        std::memcpy(m_SmallData, other.m_SmallData, other.m_DataSize);
    } else {
        m_LargeData = new char[other.m_DataSize];
        std::memcpy(m_LargeData, other.m_LargeData, other.m_DataSize);
    }

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
    m_IsSmall = other.m_IsSmall;
    m_DataSize = other.m_DataSize;
    if (m_IsSmall) {
        std::memcpy(m_SmallData, other.m_SmallData, other.m_DataSize);
    } else {
        m_LargeData = other.m_LargeData;
        other.m_LargeData = nullptr;
        other.m_DataSize = 0;
    }

    // Success
    return *this;
}

bool ByteArray::operator==(const ByteArray &other) const noexcept
{
    if (m_IsSmall != other.m_IsSmall || m_DataSize != other.m_DataSize) {
        return false;
    }

    if (m_IsSmall) {
        return std::memcmp(m_SmallData, other.m_SmallData, m_DataSize) == 0;
    } else {
        return std::memcmp(m_LargeData, other.m_LargeData, m_DataSize) == 0;
    }
}

const char *ByteArray::data() const noexcept
{
    return m_IsSmall ? m_SmallData : m_LargeData;
}

void ByteArray::clear() noexcept
{
    if (m_IsSmall) {
        m_DataSize = 0;
    } else if (m_LargeData) {
        delete[] m_LargeData;
        m_LargeData = nullptr;
        m_DataSize = 0;
    }
}

} // namespace checo