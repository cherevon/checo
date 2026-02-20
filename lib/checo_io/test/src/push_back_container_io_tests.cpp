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
#include "checo/push_back_container_io.h"

#include <gtest/gtest.h>

#include <deque>
#include <list>
#include <sstream>
#include <vector>

namespace checo::testing
{

template <typename T>
class PushBackContainerFixture : public ::testing::Test
{
};

using PushBackContainerTypes = ::testing::Types<std::vector<int>, std::list<int>, std::deque<int>>;
TYPED_TEST_SUITE(PushBackContainerFixture, PushBackContainerTypes);

TYPED_TEST(PushBackContainerFixture, BinaryReadWrite)
{
    static constexpr size_t ITEM_COUNT = 33;

    using T = TypeParam;

    // Create a container and fill it with test data
    T expectedContainer;
    for (size_t i = 0; i < ITEM_COUNT; ++i)
    {
        expectedContainer.push_back(static_cast<int>(i * i)); // Fill with squares of indices
    }

    // Write expected data to the stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    writeBinary(stream, expectedContainer, writeBinary<int>);

    // Read data back from the stream
    stream.seekg(0);
    T readContainer{};
    readBinary(stream, readContainer, readBinary<int>);

    // Check that the read container matches the expected one
    ASSERT_EQ(expectedContainer, readContainer);
}

} // namespace checo::testing