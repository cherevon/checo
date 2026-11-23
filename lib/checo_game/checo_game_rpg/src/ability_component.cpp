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

EntityId AbilityComponent::addAbility(const AbilityInstance &abilityInstance)
{
    // Add the ability to the list and assign it a unique instance ID
    auto &newAbilityInstance = m_Abilities.emplace_back(abilityInstance);
    newAbilityInstance.m_InstanceId = m_NextInstanceId++;

    // Return newly assigned instance ID
    return newAbilityInstance.m_InstanceId;
}

void AbilityComponent::removeAbility(const EntityId instanceId)
{
    // Find the ability to be removed
    std::erase_if(m_Abilities, [&](const auto &ability) { return ability.m_InstanceId == instanceId; });
}

void AbilityComponent::removeAbilitiesByDefinitionId(const EntityId definitionId)
{
    std::erase_if(m_Abilities, [&](const auto &ability) { return ability.m_DefinitionId == definitionId; });
}

void AbilityComponent::removeAbilitiesBySourceId(const EntityId sourceId)
{
    std::erase_if(m_Abilities, [&](const auto &ability) { return ability.m_SourceId == sourceId; });
}

bool AbilityComponent::hasAbility(const EntityId instanceId) const
{
    return std::ranges::any_of(m_Abilities, std::bind_front(std::equal_to{}, instanceId),
        &AbilityInstance::m_InstanceId);
}

bool AbilityComponent::hasAbilityByDefinitionId(const EntityId definitionId) const
{
    return std::ranges::any_of(m_Abilities, std::bind_front(std::equal_to{}, definitionId),
        &AbilityInstance::m_DefinitionId);
}

bool AbilityComponent::hasAbilityBySourceId(const EntityId sourceId) const
{
    return std::ranges::any_of(m_Abilities, std::bind_front(std::equal_to{}, sourceId), &AbilityInstance::m_SourceId);
}

void AbilityComponent::clearAbilities()
{
    m_Abilities.clear();
}

} // namespace checo::game