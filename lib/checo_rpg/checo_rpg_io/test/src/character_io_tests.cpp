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

#include "checo/rpg/character_io.h"
#include "checo/rpg/character_test_support.h"

#include <gtest/gtest.h>

#include <sstream>

namespace checo::rpg::testing
{

class CharacterIoTest : public ::testing::TestWithParam<checo::rpg::Character>
{
};

TEST_P(CharacterIoTest, BinaryReadWrite)
{
    const checo::rpg::Character expectedCharacter = GetParam();

    // Write expected character to a binary stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    checo::rpg::writeBinary(stream, expectedCharacter, writeTestStat, writeTestInventory, writeTestAbility,
        writeTestStatusEffect);

    // Read character back from the stream
    stream.seekg(0);
    checo::rpg::Character readCharacter{};
    checo::rpg::readBinary(stream, readCharacter, readTestStat, readTestInventory, readTestAbility,
        readTestStatusEffect);

    // Verify that the read character matches the expected one
    ASSERT_TRUE(deepEqual(expectedCharacter, readCharacter));
}

INSTANTIATE_TEST_SUITE_P(CharacterCases, CharacterIoTest,
    ::testing::ValuesIn({
        checo::rpg::Character{},
        *createTestCharacter(12345, 0, 0, 0, 0, 0),
        *createTestCharacter(12346, 0, 0, 0, 0, 7),
        *createTestCharacter(12347, 0, 0, 0, 7, 0),
        *createTestCharacter(12348, 0, 0, 7, 0, 0),
        *createTestCharacter(12349, 0, 7, 0, 0, 0),
        *createTestCharacter(12350, 7, 0, 0, 0, 0),
        *createTestCharacter(12351, 10, 20, 30, 40, 50),
        *createTestCharacter(12352, 50, 40, 30, 20, 10),
    }));

} // namespace checo::rpg::testing