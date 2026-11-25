/*
 * MIT License
 *
 * Copyright (c) 2026 Sergei Cherevichko
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

#include "checo/game/ability_component.h"

#include <algorithm>
#include <functional>

namespace checo::game
{

void AbilityComponent::addAbility(const AbilityInstance &abilityInstance)
{
    m_Abilities.push_back(abilityInstance);
}

void AbilityComponent::removeAbility(EntityId instanceId)
{
    std::erase_if(m_Abilities, [&](const auto &ability) { return ability.m_InstanceId == instanceId; });
}

void AbilityComponent::removeAbilitiesByDefinitionId(EntityId definitionId)
{
    std::erase_if(m_Abilities, [&](const auto &ability) { return ability.m_DefinitionId == definitionId; });
}

void AbilityComponent::removeAbilitiesBySourceId(EntityId sourceId, EntityType sourceType)
{
    std::erase_if(m_Abilities,
        [&](const auto &ability) { return ability.m_SourceType == sourceType && ability.m_SourceId == sourceId; });
}

bool AbilityComponent::hasAbility(EntityId instanceId) const
{
    return std::ranges::any_of(m_Abilities, std::bind_front(std::equal_to{}, instanceId),
        &AbilityInstance::m_InstanceId);
}

bool AbilityComponent::hasAbilityByDefinitionId(EntityId definitionId) const
{
    return std::ranges::any_of(m_Abilities, std::bind_front(std::equal_to{}, definitionId),
        &AbilityInstance::m_DefinitionId);
}

bool AbilityComponent::hasAbilityBySourceId(EntityId sourceId, EntityType sourceType) const
{
    return std::ranges::any_of(m_Abilities, [&](const AbilityInstance &ability) {
        return ability.m_SourceType == sourceType && ability.m_SourceId == sourceId;
    });
}

void AbilityComponent::clearAbilities()
{
    m_Abilities.clear();
}

} // namespace checo::game