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

#include "checo/rpg/entity_io.h"

#include "checo/fundamental_io.h"
#include "checo/string_io.h"

namespace checo::rpg
{

void readBinary(std::istream &inStream, Entity &data)
{
    checo::readBinary(inStream, data.m_Id);
    checo::readBinary(inStream, data.m_Category);
    checo::readBinary(inStream, data.m_Name);
    checo::readBinary(inStream, data.m_Description);
}

void writeBinary(std::ostream &outStream, const Entity &data)
{
    checo::writeBinary(outStream, data.m_Id);
    checo::writeBinary(outStream, data.m_Category);
    checo::writeBinary(outStream, data.m_Name);
    checo::writeBinary(outStream, data.m_Description);
}

} // namespace checo::rpg