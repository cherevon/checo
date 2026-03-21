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

#include "checo/rpg/inventory_test_support.h"
#include "checo/rpg/currency_test_support.h"
#include "checo/rpg/entity_test_support.h"
#include "checo/rpg/item_test_support.h"
#include "test_support.h"

#include <algorithm>

namespace checo::rpg::testing
{

static constexpr const char *ENTITY_TYPE = "InventoryItem";

bool deepEqual(const Inventory &left, const Inventory &right)
{
    // Check entity data
    if (!deepEqual(static_cast<const Entity &>(left), static_cast<const Entity &>(right))) {
        return false;
    }

    // Check items
    if (!std::ranges::equal(left.m_Items, right.m_Items,
            [](const auto &leftItem, const auto &rightItem) { return deepEqual(leftItem, rightItem); })) {
        return false;
    }

    // Check currencies
    if (!std::ranges::equal(left.m_Currencies, right.m_Currencies,
            [](const auto &leftCurrency, const auto &rightCurrency) {
                return deepEqual(leftCurrency, rightCurrency);
            })) {
        return false;
    }

    // Success
    return true;
}

bool deepEqual(const InventoryItem &left, const InventoryItem &right)
{
    return left.m_Count == right.m_Count && deepEqual(*left.m_Item, *right.m_Item);
}

bool deepEqual(const InventoryCurrency &left, const InventoryCurrency &right)
{
    return left.m_Count == right.m_Count && deepEqual(*left.m_Currency, *right.m_Currency);
}

std::shared_ptr<Inventory> createTestInventory(const UniqueId &id, const size_t itemCount, const size_t currencyCount)
{
    // Fill entity data
    auto result = std::make_shared<Inventory>();
    result->m_Id = id;
    result->m_Category = createTestCategory(ENTITY_TYPE, result->m_Id);
    result->m_Name = createTestName(ENTITY_TYPE, result->m_Id);
    result->m_Description = createTestDescription(ENTITY_TYPE, result->m_Id);

    // Fill items
    for (size_t i = 0; i < itemCount; ++i) {
        result->m_Items.push_back(InventoryItem{.m_Item = createTestItem(i), .m_Count = static_cast<uint32_t>(i * i)});
    }

    // Fill currencies
    for (size_t i = 0; i < currencyCount; ++i) {
        result->m_Currencies.push_back(
            InventoryCurrency{.m_Currency = createTestCurrency(i), .m_Count = static_cast<uint32_t>(i * i)});
    }

    // Success
    return result;
}

} // namespace checo::rpg::testing