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

#include "checo/byte_array.h"

#include <gtest/gtest.h>

#include <cstring>

namespace checo::testing
{

static const std::string LARGE_STRING = std::string(1000, 'x');

struct ByteArrayTestCase
{
    const char *m_Data{nullptr};
    uint64_t m_DataSize{0};
};

class ByteArrayTest : public ::testing::TestWithParam<ByteArrayTestCase>
{
};

TEST_P(ByteArrayTest, StoreData)
{
    const ByteArrayTestCase &testCase = GetParam();

    checo::ByteArray testByteArray(testCase.m_Data, testCase.m_DataSize);
    ASSERT_EQ(testByteArray.size(), testCase.m_DataSize);
    ASSERT_EQ(std::memcmp(testByteArray.data(), testCase.m_Data, testCase.m_DataSize), 0);
}

INSTANTIATE_TEST_SUITE_P(DifferentSizeData, ByteArrayTest,
    ::testing::Values(ByteArrayTestCase{nullptr, 0}, ByteArrayTestCase{"abcd", 4}, ByteArrayTestCase{"12345678", 8},
        ByteArrayTestCase{LARGE_STRING.c_str(), LARGE_STRING.size()}));

} // namespace checo::testing