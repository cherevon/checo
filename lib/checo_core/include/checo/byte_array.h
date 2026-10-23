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

#include <cstdint>

namespace checo
{

class CHECO_CORE_EXPORT ByteArray final
{
  public:
    ByteArray() noexcept;
    ByteArray(const char *data, uint64_t dataSize);

    ByteArray(const ByteArray &other);
    ByteArray(ByteArray &&other) noexcept;

    ~ByteArray() noexcept;

  public:
    ByteArray &operator=(const ByteArray &other);
    ByteArray &operator=(ByteArray &&other) noexcept;

    bool operator==(const ByteArray &other) const noexcept;

  public:
    inline uint64_t size() const noexcept { return m_DataSize; }

    const char *data() const noexcept;

    void clear() noexcept;

  private:
    static constexpr uint64_t MAX_SMALL_DATA_SIZE{16};

    bool m_IsSmall{true};
    uint64_t m_DataSize{0};

    union
    {
        char m_SmallData[MAX_SMALL_DATA_SIZE];
        char *m_LargeData{nullptr};
    };
};

} // namespace checo