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
#include "checo/set_io.h"

#include <gtest/gtest.h>

#include <cmath>
#include <set>
#include <sstream>
#include <unordered_set>

namespace checo::testing
{

template <typename T>
class SetContainerFixture : public ::testing::Test
{
};

using SetContainerTypes =
    ::testing::Types<std::set<int>, std::unordered_set<int>, std::multiset<int>, std::unordered_multiset<int>>;
TYPED_TEST_SUITE(SetContainerFixture, SetContainerTypes);

TYPED_TEST(SetContainerFixture, BinaryReadWrite)
{
    static constexpr int ITEM_COUNT = 33;

    using T = TypeParam;

    // Create a container and fill it with test data
    T expectedContainer;
    for (int i = 0; i < ITEM_COUNT; ++i)
    {
        expectedContainer.insert(i);
        expectedContainer.insert(i); // Insert duplicate keys for multisets
    }

    // Write expected data to the stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    checo::writeBinary(stream, expectedContainer, checo::writeBinary<int>);

    // Read data back from the stream
    stream.seekg(0);
    T readContainer{};
    checo::readBinary(stream, readContainer, checo::readBinary<int>);

    // Check that the read container matches the expected one
    ASSERT_NE(expectedContainer.size(), 0);
    ASSERT_EQ(expectedContainer.size(), readContainer.size());
    ASSERT_EQ(expectedContainer, readContainer);
}

} // namespace checo::testing