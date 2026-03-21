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

#include "checo/rpg/character_test_support.h"
#include "checo/rpg/ability_test_support.h"
#include "checo/rpg/currency_test_support.h"
#include "checo/rpg/entity_test_support.h"
#include "checo/rpg/inventory_test_support.h"
#include "checo/rpg/item_test_support.h"
#include "checo/rpg/stat_test_support.h"
#include "checo/rpg/status_effect_test_support.h"
#include "test_support.h"

#include <algorithm>

namespace checo::rpg::testing
{

static constexpr const char *ENTITY_TYPE = "Character";

bool deepEqual(const Character &left, const Character &right)
{
    // Check entity data
    if (!deepEqual(static_cast<const Entity &>(left), static_cast<const Entity &>(right))) {
        return false;
    }

    // Check stats
    if (!std::ranges::equal(left.m_Stats, right.m_Stats, [](const auto &leftStat, const auto &rightStat) {
            return leftStat.m_Value == rightStat.m_Value && deepEqual(*leftStat.m_Stat, *rightStat.m_Stat);
        })) {
        return false;
    }

    // Check inventory
    if ((left.m_Inventory && !right.m_Inventory) || (!left.m_Inventory && right.m_Inventory) ||
        (left.m_Inventory && right.m_Inventory && !deepEqual(*left.m_Inventory, *right.m_Inventory))) {
        return false;
    }

    // Check abilities
    if (!std::ranges::equal(left.m_Abilities, right.m_Abilities,
            [](const auto &leftAbility, const auto &rightAbility) { return deepEqual(*leftAbility, *rightAbility); })) {
        return false;
    }

    // Check status effects
    if (!std::ranges::equal(left.m_StatusEffects, right.m_StatusEffects,
            [](const auto &leftStatusEffect, const auto &rightStatusEffect) {
                return deepEqual(*leftStatusEffect, *rightStatusEffect);
            })) {
        return false;
    }

    // Success
    return true;
}

std::shared_ptr<Character> createTestCharacter(const UniqueId &id, const size_t statCount, const size_t itemCount,
    const size_t currencyCount, const size_t abilityCount, const size_t statusEffectCount)
{
    // Fill entity data
    auto result = std::make_shared<Character>();
    result->m_Id = id;
    result->m_Category = createTestCategory(ENTITY_TYPE, result->m_Id);
    result->m_Name = createTestName(ENTITY_TYPE, result->m_Id);
    result->m_Description = createTestDescription(ENTITY_TYPE, result->m_Id);

    // Fill stats
    for (size_t i = 0; i < statCount; ++i) {
        result->m_Stats.push_back(CharacterStat{.m_Stat = createTestStat(i), .m_Value = static_cast<int8_t>(i)});
    }

    // Fill inventory
    result->m_Inventory = createTestInventory(itemCount, currencyCount);

    // Fill abilities
    for (size_t i = 0; i < abilityCount; ++i) {
        result->m_Abilities.push_back(createTestAbility(i));
    }

    // Fill status effects
    for (size_t i = 0; i < statusEffectCount; ++i) {
        result->m_StatusEffects.push_back(createTestStatusEffect(i));
    }

    // Success
    return result;
}

} // namespace checo::rpg::testing