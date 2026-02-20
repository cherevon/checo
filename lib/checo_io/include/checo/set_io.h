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

#include "fundamental_io.h"

#include <functional>
#include <iostream>

namespace checo
{

template <typename T>
concept SetContainer = requires(T container, typename T::value_type value) {
    container.insert(value);
    container.size();
} && std::same_as<typename T::key_type, typename T::value_type>;

template <SetContainer T>
void readBinary(std::istream &inStream, T &container,
    const std::function<void(std::istream &, typename T::value_type &)> &readItemFunc)
{
    // Read the size of the container first
    decltype(container.size()) size{0};
    checo::readBinary(inStream, size);

    // Read each item from the stream and insert it into the container
    for (decltype(size) itemNum = 0; itemNum < size; ++itemNum)
    {
        typename T::value_type item{};
        readItemFunc(inStream, item);
        container.insert(item);
    }
}

template <SetContainer T>
void writeBinary(std::ostream &outStream, const T &container,
    const std::function<void(std::ostream &, const typename T::value_type &)> &writeItemFunc)
{
    // Write the size of the container first
    const auto size = container.size();
    checo::writeBinary(outStream, size);

    // Write each item to the stream
    for (const auto &item : container)
    {
        writeItemFunc(outStream, item);
    }
}

} // namespace checo