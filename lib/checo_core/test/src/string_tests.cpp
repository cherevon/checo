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

#include "checo/string.h"

#include <gtest/gtest.h>

#include <cstring>

namespace checo::testing
{

class StringTest : public ::testing::TestWithParam<std::tuple<std::string, std::string>>
{
};

TEST(StringTest, DefaultConstructor)
{
    checo::String testString;
    ASSERT_EQ(testString.size(), 0);
    ASSERT_EQ(testString, "");
    ASSERT_EQ(*(testString.data()), '\0');
}

TEST_P(StringTest, ComparisonOperators)
{
    const auto &[stdStr1, stdStr2] = GetParam();

    checo::String str1(stdStr1);
    checo::String str2(stdStr2);

    ASSERT_EQ(str1 == str2, stdStr1 == stdStr2);
    ASSERT_EQ(str1 > str2, stdStr1 > stdStr2);
    ASSERT_EQ(str1 < str2, stdStr1 < stdStr2);
    ASSERT_EQ(str1 != str2, stdStr1 != stdStr2);
    ASSERT_EQ(str1 >= str2, stdStr1 >= stdStr2);
    ASSERT_EQ(str1 <= str2, stdStr1 <= stdStr2);
}

TEST_P(StringTest, Size)
{
    const auto &[stdStr1, stdStr2] = GetParam();

    checo::String testString(stdStr1);
    ASSERT_EQ(testString.size(), stdStr1.size());
}

TEST_P(StringTest, Data)
{
    const auto &[stdStr1, stdStr2] = GetParam();

    checo::String testString(stdStr1);
    ASSERT_EQ(std::memcmp(testString.data(), stdStr1.data(), stdStr1.size()), 0);
}

TEST_P(StringTest, Clear)
{
    const auto &[stdStr1, stdStr2] = GetParam();

    checo::String testString(stdStr1);
    testString.clear();
    ASSERT_EQ(testString.size(), 0);
    ASSERT_EQ(testString, "");
}

static const std::vector<std::string> TEST_STRINGS = {
    "",
    "abcd",
    "abcdefgh",
    std::string(1000, 'x'),
};

INSTANTIATE_TEST_SUITE_P(DifferentStrings, StringTest,
    ::testing::Combine(::testing::ValuesIn(TEST_STRINGS), ::testing::ValuesIn(TEST_STRINGS)));

} // namespace checo::testing