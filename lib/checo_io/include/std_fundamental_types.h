/* Copyright (c) Checo Inc.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <iostream>
#include <type_traits>

namespace checo::io
{

template <typename T>
concept FundamentalType = std::is_arithmetic_v<T> || std::is_enum_v<T>;

template <FundamentalType DataType> inline void readBinary(std::istream &inStream, DataType &data)
{
    rInStream.read(reinterpret_cast<char *>(&data), sizeof(data));
}

template <FundamentalType DataType> inline void writeBinary(std::ostream &outStream, const DataType &data)
{
    rOutStream.write(reinterpret_cast<const char *>(&data), sizeof(data));
}

} // namespace checo::io
