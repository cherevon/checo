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

#include "checo/rpg/item_test_support.h"
#include "checo/rpg/ability_test_support.h"
#include "checo/rpg/entity_test_support.h"
#include "checo/rpg/status_effect_test_support.h"
#include "test_support.h"

#include <algorithm>

namespace checo::rpg
{

static constexpr const char *ENTITY_TYPE = "Item";

bool deepEqual(const Item &left, const Item &right)
{
    // Check entity data
    if (!deepEqual(static_cast<const Entity &>(left), static_cast<const Entity &>(right))) {
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

std::shared_ptr<Item> createTestItem(const size_t abilityCount, const size_t statusEffectCount)
{
    // Fill entity data
    auto result = std::make_shared<Item>();
    result->m_Id = getNextTestEntityId();
    result->m_Category = createTestCategory(ENTITY_TYPE, result->m_Id);
    result->m_Name = createTestName(ENTITY_TYPE, result->m_Id);
    result->m_Description = createTestDescription(ENTITY_TYPE, result->m_Id);

    // Fill abilities
    for (size_t i = 0; i < abilityCount; ++i) {
        result->m_Abilities.push_back(createTestAbility());
    }

    // Fill status effects
    for (size_t i = 0; i < statusEffectCount; ++i) {
        result->m_StatusEffects.push_back(createTestStatusEffect());
    }

    // Success
    return result;
}

} // namespace checo::rpg