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

#include "checo/rpg/ability.h"
#include "checo/rpg/currency.h"
#include "checo/rpg/inventory.h"
#include "checo/rpg/item.h"
#include "checo/rpg/stat.h"
#include "checo/rpg/status_effect.h"

#include <iostream>
#include <memory>

namespace checo::rpg::testing
{

std::shared_ptr<Ability> readTestAbility(std::istream &inStream);
void writeTestAbility(std::ostream &outStream, const std::shared_ptr<Ability> &ability);

std::shared_ptr<StatusEffect> readTestStatusEffect(std::istream &inStream);
void writeTestStatusEffect(std::ostream &outStream, const std::shared_ptr<StatusEffect> &statusEffect);

std::shared_ptr<Currency> readTestCurrency(std::istream &inStream);
void writeTestCurrency(std::ostream &outStream, const std::shared_ptr<Currency> &currency);

std::shared_ptr<Item> readTestItem(std::istream &inStream);
void writeTestItem(std::ostream &outStream, const std::shared_ptr<Item> &item);

std::shared_ptr<Stat> readTestStat(std::istream &inStream);
void writeTestStat(std::ostream &outStream, const std::shared_ptr<Stat> &stat);

std::shared_ptr<Inventory> readTestInventory(std::istream &inStream);
void writeTestInventory(std::ostream &outStream, const std::shared_ptr<Inventory> &inventory);

} // namespace checo::rpg::testing