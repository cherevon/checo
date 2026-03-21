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

#include "checo/rpg/currency_io.h"
#include "checo/rpg/currency_test_support.h"

#include <gtest/gtest.h>

#include <sstream>

namespace checo::rpg::testing
{

class CurrencyIoTest : public ::testing::TestWithParam<checo::rpg::Currency>
{
};

TEST_P(CurrencyIoTest, BinaryReadWrite)
{
    const checo::rpg::Currency expectedCurrency = GetParam();

    // Write expected currency to a binary stream
    std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);
    checo::rpg::writeBinary(stream, expectedCurrency);

    // Read currency back from the stream
    stream.seekg(0);
    checo::rpg::Currency readCurrency{};
    checo::rpg::readBinary(stream, readCurrency);

    // Verify that the read currency matches the expected one
    ASSERT_TRUE(deepEqual(expectedCurrency, readCurrency));
}

INSTANTIATE_TEST_SUITE_P(CurrencyCases, CurrencyIoTest,
    ::testing::ValuesIn({
        checo::rpg::Currency{},
        *createTestCurrency(12345),
    }));

} // namespace checo::rpg::testing