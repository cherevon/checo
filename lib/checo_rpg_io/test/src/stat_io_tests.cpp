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

#include "checo/rpg/stat_io.h"
#include "checo/rpg/stat_test_support.h"

#include <gtest/gtest.h>

#include <sstream>

namespace checo::rpg::testing
{

class StatIoTest : public ::testing::TestWithParam<checo::rpg::Stat>
{
};

TEST_P(StatIoTest, BinaryReadWrite)
{
    const checo::rpg::Stat expectedStat = GetParam();

    // Write expected stat to a binary stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    checo::rpg::writeBinary(stream, expectedStat);

    // Read stat back from the stream
    stream.seekg(0);
    checo::rpg::Stat readStat{};
    checo::rpg::readBinary(stream, readStat);

    // Verify that the read stat matches the expected one
    ASSERT_TRUE(deepEqual(expectedStat, readStat));
}

INSTANTIATE_TEST_SUITE_P(StatCases, StatIoTest,
    ::testing::ValuesIn({
        checo::rpg::Stat{},
        *checo::rpg::createTestStat(),
    }));

} // namespace checo::rpg::testing