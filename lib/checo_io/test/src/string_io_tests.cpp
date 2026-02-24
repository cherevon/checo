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

#include "checo/string_io.h"

#include <gtest/gtest.h>

#include <sstream>

namespace checo::testing
{

class StringIoTest : public ::testing::TestWithParam<std::string>
{
};

TEST_P(StringIoTest, BinaryReadWrite)
{
    const std::string expectedString = GetParam();

    // Write expected string to a binary stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    checo::writeBinary(stream, expectedString);

    // Read string back from the stream
    stream.seekg(0);
    std::string readString;
    checo::readBinary(stream, readString);

    // Verify that the read string matches the expected one
    EXPECT_EQ(expectedString, readString);
}

INSTANTIATE_TEST_SUITE_P(StringCases, StringIoTest,
    ::testing::Values(std::string{},           // empty
        std::string{"a"},                      // single char
        std::string{"hello"},                  // simple ascii
        std::string{"with spaces inside"},     // spaces
        std::string{"in \0 the middle", 16},   // embedded nulls
        std::string{"line1\nline2\n"},         // newlines
        std::string{"!@#$%^&*()_+-=[]{};':,."} // punctuation
        ));

} // namespace checo::testing