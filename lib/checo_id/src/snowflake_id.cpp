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

#include "checo/id/snowflake_id.h"

#include <chrono>
#include <stdexcept>

namespace checo::id
{

static int64_t currentMilliseconds()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

SnowflakeIdGenerator::SnowflakeIdGenerator(std::uint16_t workerId)
    : m_WorkerId{workerId}
{
    if (m_WorkerId > MAX_WORKER_ID)
    {
        throw std::runtime_error("workerId out of range");
    }
}

SnowflakeIdGenerator::~SnowflakeIdGenerator() = default;

int64_t SnowflakeIdGenerator::nextId()
{
    using namespace std::chrono;

    // Get current timestamp in milliseconds
    int64_t timestamp = currentMilliseconds();
    if (timestamp < m_LastTimestamp)
    {
        throw std::runtime_error("clock moved backwards");
    }

    // If we're in the same millisecond as the last ID, increment the sequence
    if (timestamp == m_LastTimestamp)
    {
        // Same ms -> increment sequence
        std::uint16_t seq = ++m_Sequence;
        if (seq > SEQUENCE_MASK)
        {
            // Sequence overflow in same ms -> wait for next ms
            do
            {
                timestamp = currentMilliseconds();
            } while (timestamp <= m_LastTimestamp);
            m_Sequence = 0;
        }
    }
    else
    {
        m_Sequence = 0;
    }

    // Update last timestamp
    m_LastTimestamp = timestamp;

    // Construct the ID by combining timestamp, worker ID, and sequence
    return ((timestamp - EPOCH) << TIMESTAMP_SHIFT) | (static_cast<int64_t>(m_WorkerId) << WORKER_ID_SHIFT) |
           m_Sequence.load();
}

} // namespace checo::id