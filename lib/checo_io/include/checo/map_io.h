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

#include <functional>
#include <iostream>

namespace checo
{

template <typename T>
concept MapContainer = requires(T container, typename T::key_type key, typename T::mapped_type value) {
    container.emplace(key, value);
    container.size();
};

template <MapContainer T>
void readBinary(std::istream &inStream, T &container,
    const std::function<void(std::istream &, typename T::key_type &)> &readKeyFunc,
    const std::function<void(std::istream &, typename T::mapped_type &)> &readValueFunc)
{
    // Read the size of the container first
    decltype(container.size()) size{0};
    inStream.read(reinterpret_cast<char *>(&size), sizeof(size));

    // Read each key-value pair from the stream and insert it into the container
    for (decltype(size) itemNum = 0; itemNum < size; ++itemNum)
    {
        typename T::key_type key{};
        typename T::mapped_type value{};
        readKeyFunc(inStream, key);
        readValueFunc(inStream, value);

        container.emplace(key, value);
    }
}

template <MapContainer T>
void writeBinary(std::ostream &outStream, const T &container,
    const std::function<void(std::ostream &, const typename T::key_type &)> &writeKeyFunc,
    const std::function<void(std::ostream &, const typename T::mapped_type &)> &writeValueFunc)
{
    // Write the size of the container first
    const auto size = container.size();
    outStream.write(reinterpret_cast<const char *>(&size), sizeof(size));

    // Write each key-value pair to the stream
    for (const auto &[key, value] : container)
    {
        writeKeyFunc(outStream, key);
        writeValueFunc(outStream, value);
    }
}

} // namespace checo