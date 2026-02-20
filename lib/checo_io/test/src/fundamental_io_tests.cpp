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

#include "checo/fundamental_io.h"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <vector>

namespace checo::testing
{

template <typename T>
class FundamentalIoFixture : public ::testing::Test
{
};

using FundamentalTypes = ::testing::Types<bool, char, signed char, unsigned char, short, unsigned short, int,
    unsigned int, long long, unsigned long long, float, double>;
TYPED_TEST_SUITE(FundamentalIoFixture, FundamentalTypes);

TYPED_TEST(FundamentalIoFixture, BinaryReadWrite)
{
    using T = TypeParam;

    // Define test values for the type T, covering edge cases
    std::vector<T> testValues = {
        T{},                           // default / zero
        std::numeric_limits<T>::min(), // smallest (most negative for signed)
        std::numeric_limits<T>::max()  // largest
    };

    // For floating-point types, also include special values
    if constexpr (std::is_floating_point_v<T>)
    {
        testValues.push_back(std::numeric_limits<T>::quiet_NaN()); // NaN
        testValues.push_back(std::numeric_limits<T>::infinity());  // +inf
        testValues.push_back(-std::numeric_limits<T>::infinity()); // -inf
    }

    // Test writing and reading back each value
    for (T expectedData : testValues)
    {
        std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);

        // Write expected data to the stream
        writeBinary(stream, expectedData);
        stream.seekg(0);

        // Read data back from the stream
        T readData{};
        readBinary(stream, readData);

        // Check that the read data matches the expected data
        if constexpr (std::is_floating_point_v<T>)
        {
            // For floating-point types, we use a tolerance-based comparison
            if (std::isnan(expectedData))
            {
                ASSERT_TRUE(std::isnan(readData));
            }
            else if (std::isinf(expectedData))
            {
                ASSERT_TRUE(std::isinf(readData) && (std::signbit(expectedData) == std::signbit(readData)));
            }
            else
            {
                ASSERT_NEAR(expectedData, readData, std::numeric_limits<T>::epsilon());
            }
        }
        else
        {
            // For integral types, we can check for exact equality
            ASSERT_EQ(expectedData, readData);
        }
    }
}

} // namespace checo::testing