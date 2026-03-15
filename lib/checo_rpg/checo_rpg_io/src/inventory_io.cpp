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

#include "checo/rpg/inventory_io.h"
#include "checo/rpg/currency_io.h"
#include "checo/rpg/entity_io.h"
#include "checo/rpg/item_io.h"

#include "checo/fundamental_io.h"
#include "checo/vector_io.h"

namespace checo::rpg
{

using ItemReader = std::function<std::shared_ptr<Item>(std::istream &)>;
using ItemWriter = std::function<void(std::ostream &, const std::shared_ptr<Item> &)>;

using CurrencyReader = std::function<std::shared_ptr<Currency>(std::istream &)>;
using CurrencyWriter = std::function<void(std::ostream &, const std::shared_ptr<Currency> &)>;

void readBinary(std::istream &inStream, InventoryItem &data, const ItemReader &readItemFunc)
{
    // Read item
    data.m_Item = readItemFunc(inStream);

    // Read count
    checo::readBinary(inStream, data.m_Count);
}

void writeBinary(std::ostream &outStream, const InventoryItem &data, const ItemWriter &writeItemFunc)
{
    // Write item
    writeItemFunc(outStream, data.m_Item);

    // Write count
    checo::writeBinary(outStream, data.m_Count);
}

void readBinary(std::istream &inStream, InventoryCurrency &data, const CurrencyReader &readCurrencyFunc)
{
    // Read currency
    data.m_Currency = readCurrencyFunc(inStream);

    // Read count
    checo::readBinary(inStream, data.m_Count);
}

void writeBinary(std::ostream &outStream, const InventoryCurrency &data, const CurrencyWriter &writeCurrencyFunc)
{
    // Write currency
    writeCurrencyFunc(outStream, data.m_Currency);

    // Write count
    checo::writeBinary(outStream, data.m_Count);
}

void readBinary(std::istream &inStream, Inventory &data, const ItemReader &readItemFunc,
    const CurrencyReader &readCurrencyFunc)
{
    // Read entity data
    readBinary(inStream, static_cast<Entity &>(data));

    // Read items
    const auto readItemFuncWrapper = [&](std::istream &stream, InventoryItem &invItem) {
        readBinary(stream, invItem, readItemFunc);
    };
    checo::readBinary(inStream, data.m_Items, readItemFuncWrapper);

    // Read currencies
    const auto readCurrencyFuncWrapper = [&](std::istream &stream, InventoryCurrency &invCurrency) {
        readBinary(stream, invCurrency, readCurrencyFunc);
    };
    checo::readBinary(inStream, data.m_Currencies, readCurrencyFuncWrapper);
}

void writeBinary(std::ostream &outStream, const Inventory &data, const ItemWriter &writeItemFunc,
    const CurrencyWriter &writeCurrencyFunc)
{
    // Write entity data
    writeBinary(outStream, static_cast<const Entity &>(data));

    // Write items
    const auto writeItemFuncWrapper = [&](std::ostream &stream, const InventoryItem &invItem) {
        writeBinary(stream, invItem, writeItemFunc);
    };
    checo::writeBinary(outStream, data.m_Items, writeItemFuncWrapper);

    // Write currencies
    const auto writeCurrencyFuncWrapper = [&](std::ostream &stream, const InventoryCurrency &invCurrency) {
        writeBinary(stream, invCurrency, writeCurrencyFunc);
    };
    checo::writeBinary(outStream, data.m_Currencies, writeCurrencyFuncWrapper);
}

} // namespace checo::rpg