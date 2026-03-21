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
#include "checo/rpg/currency_io.h"
#include "checo/rpg/inventory_io.h"
#include "checo/rpg/item_io.h"
#include "checo/rpg/stat_io.h"
#include "checo/rpg/status_effect_io.h"

namespace checo::rpg::testing
{

std::shared_ptr<Ability> readTestAbility(std::istream &inStream)
{
    auto ability = std::make_shared<checo::rpg::Ability>();
    checo::rpg::readBinary(inStream, *ability);
    return ability;
}

void writeTestAbility(std::ostream &outStream, const std::shared_ptr<Ability> &ability)
{
    checo::rpg::writeBinary(outStream, *ability);
}

std::shared_ptr<StatusEffect> readTestStatusEffect(std::istream &inStream)
{
    auto statusEffect = std::make_shared<checo::rpg::StatusEffect>();
    checo::rpg::readBinary(inStream, *statusEffect);
    return statusEffect;
}

void writeTestStatusEffect(std::ostream &outStream, const std::shared_ptr<StatusEffect> &statusEffect)
{
    checo::rpg::writeBinary(outStream, *statusEffect);
}

std::shared_ptr<Currency> readTestCurrency(std::istream &inStream)
{
    auto currency = std::make_shared<checo::rpg::Currency>();
    checo::rpg::readBinary(inStream, *currency);
    return currency;
}

void writeTestCurrency(std::ostream &outStream, const std::shared_ptr<Currency> &currency)
{
    checo::rpg::writeBinary(outStream, *currency);
}

std::shared_ptr<Item> readTestItem(std::istream &inStream)
{
    auto item = std::make_shared<checo::rpg::Item>();
    checo::rpg::readBinary(inStream, *item, readTestAbility, readTestStatusEffect);
    return item;
}

void writeTestItem(std::ostream &outStream, const std::shared_ptr<Item> &item)
{
    checo::rpg::writeBinary(outStream, *item, writeTestAbility, writeTestStatusEffect);
}

std::shared_ptr<Stat> readTestStat(std::istream &inStream)
{
    auto stat = std::make_shared<checo::rpg::Stat>();
    checo::rpg::readBinary(inStream, *stat);
    return stat;
}

void writeTestStat(std::ostream &outStream, const std::shared_ptr<Stat> &stat)
{
    checo::rpg::writeBinary(outStream, *stat);
}

std::shared_ptr<Inventory> readTestInventory(std::istream &inStream)
{
    auto inventory = std::make_shared<checo::rpg::Inventory>();
    checo::rpg::readBinary(inStream, *inventory, readTestItem, readTestCurrency);
    return inventory;
}

void writeTestInventory(std::ostream &outStream, const std::shared_ptr<Inventory> &inventory)
{
    checo::rpg::writeBinary(outStream, *inventory, writeTestItem, writeTestCurrency);
}

} // namespace checo::rpg::testing