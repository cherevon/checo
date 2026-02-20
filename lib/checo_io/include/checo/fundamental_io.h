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

#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <type_traits>

namespace checo
{

template <typename T>
concept SinglebyteArithmeticType = std::is_arithmetic_v<T> && sizeof(T) == 1;

template <typename T>
concept MultibyteArithmeticType = std::is_arithmetic_v<T> && sizeof(T) > 1;

template <SinglebyteArithmeticType T>
inline void readBinary(std::istream &inStream, T &data)
{
    inStream.read(reinterpret_cast<char *>(&data), sizeof(T));
}

template <SinglebyteArithmeticType T>
inline void writeBinary(std::ostream &outStream, const T &data)
{
    outStream.write(reinterpret_cast<const char *>(&data), sizeof(T));
}

template <MultibyteArithmeticType T>
void readBinary(std::istream &inStream, T &data)
{
    // Read bytes into a temporary array (we can't read floats/doubles directly because of potential endianness issues)
    std::array<char, sizeof(T)> buffer;
    inStream.read(buffer.data(), sizeof(T));

    // We read the data in big-endian format, so we need to swap the bytes if the host system is little-endian
    if constexpr (std::endian::native == std::endian::little)
    {
        std::ranges::reverse(buffer);
    }

    // Convert the byte array to the desired type
    data = std::bit_cast<T>(buffer);
}

template <MultibyteArithmeticType T>
void writeBinary(std::ostream &outStream, const T &data)
{
    // Convert the data to a byte array
    auto buffer = std::bit_cast<std::array<char, sizeof(T)>>(data);

    // We write the data in big-endian format, so we need to swap the bytes if the host system is little-endian
    if constexpr (std::endian::native == std::endian::little)
    {
        std::ranges::reverse(buffer);
    }

    // Write the byte array to the stream
    outStream.write(buffer.data(), sizeof(T));
}

} // namespace checo