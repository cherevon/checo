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

#include "test_support.h"

#include "checo/rpg/ability_io.h"
#include "checo/rpg/item_io.h"
#include "checo/rpg/item_test_support.h"
#include "checo/rpg/status_effect_io.h"

#include <gtest/gtest.h>

#include <sstream>

namespace checo::rpg::testing
{

class ItemIoTest : public ::testing::TestWithParam<checo::rpg::Item>
{
};

TEST_P(ItemIoTest, BinaryReadWrite)
{
    const checo::rpg::Item expectedItem = GetParam();

    // Write expected item to a binary stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    checo::rpg::writeBinary(stream, expectedItem, writeTestAbility, writeTestStatusEffect);

    // Read item back from the stream
    stream.seekg(0);
    checo::rpg::Item readItem{};
    checo::rpg::readBinary(stream, readItem, readTestAbility, readTestStatusEffect);

    // Verify that the read item matches the expected one
    ASSERT_TRUE(deepEqual(expectedItem, readItem));
}

INSTANTIATE_TEST_SUITE_P(ItemCases, ItemIoTest,
    ::testing::ValuesIn({
        checo::rpg::Item{},
        *createTestItem(12345, 0, 0),
        *createTestItem(12346, 0, 7),
        *createTestItem(12347, 7, 0),
        *createTestItem(12348, 22, 55),
        *createTestItem(12349, 55, 22),
    }));

} // namespace checo::rpg::testing