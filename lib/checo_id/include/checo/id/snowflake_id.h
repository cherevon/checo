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

#include "checo_id_export.h"

#include <atomic>
#include <cstdint>

namespace checo::id
{

class CHECO_ID_EXPORT SnowflakeIdGenerator
{
  public:
    static constexpr int64_t EPOCH = 1609459200000LL; // 2021-01-01 (ms)

    static constexpr int WORKER_ID_BITS = 10;
    static constexpr int SEQUENCE_BITS = 12;

    static constexpr int64_t MAX_WORKER_ID = (1LL << WORKER_ID_BITS) - 1;
    static constexpr int64_t SEQUENCE_MASK = (1LL << SEQUENCE_BITS) - 1;

    static constexpr int WORKER_ID_SHIFT = SEQUENCE_BITS;
    static constexpr int TIMESTAMP_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS;

  public:
    explicit SnowflakeIdGenerator(std::uint16_t worker_id);

    virtual ~SnowflakeIdGenerator();

  public:
    int64_t nextId();

  private:
    const uint16_t m_WorkerId{0};
    std::atomic_int64_t m_LastTimestamp{0};
    std::atomic_uint16_t m_Sequence{0};
};

} // namespace checo::id