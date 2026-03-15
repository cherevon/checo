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

#include "checo/rpg/ability_io.h"
#include "checo/rpg/ability_test_support.h"

#include <gtest/gtest.h>

#include <sstream>

namespace checo::rpg::testing
{

class AbilityIoTest : public ::testing::TestWithParam<checo::rpg::Ability>
{
};

TEST_P(AbilityIoTest, BinaryReadWrite)
{
    const checo::rpg::Ability expectedAbility = GetParam();

    // Write expected ability to a binary stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    checo::rpg::writeBinary(stream, expectedAbility);

    // Read ability back from the stream
    stream.seekg(0);
    checo::rpg::Ability readAbility{};
    checo::rpg::readBinary(stream, readAbility);

    // Verify that the read ability matches the expected one
    ASSERT_TRUE(deepEqual(expectedAbility, readAbility));
}

INSTANTIATE_TEST_SUITE_P(AbilityCases, AbilityIoTest,
    ::testing::ValuesIn({
        checo::rpg::Ability{},
        *checo::rpg::createTestAbility(),
    }));

} // namespace checo::rpg::testing