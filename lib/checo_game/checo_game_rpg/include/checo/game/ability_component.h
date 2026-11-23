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

#pragma once

#include "checo/game/ability.h"
#include "checo/game/actor_component.h"
#include "checo/game/entity.h"

#include <cstdint>
#include <functional>
#include <span>

namespace checo::game
{

class AbilityComponent : public ActorComponent
{
  public:
    static uint64_t getUniqueTypeId() { return 1794911747; }

  public:
    explicit AbilityComponent(Actor &actor);
    ~AbilityComponent() override = default;

  public:
    std::span<const AbilityInstance> getAbilities() const;

    EntityId addAbility(const AbilityInstance &abilityInstance);

    void removeAbility(const EntityId instanceId);
    void removeAbilitiesByDefinitionId(const EntityId definitionId);
    void removeAbilitiesBySourceId(const EntityId sourceId);

    bool hasAbility(const EntityId instanceId) const;
    bool hasAbilityByDefinitionId(const EntityId definitionId) const;
    bool hasAbilityBySourceId(const EntityId sourceId) const;

    void clearAbilities();

  private:
    Actor &m_Actor;
    std::vector<AbilityInstance> m_Abilities{};
    EntityId m_NextInstanceId{1};
};

inline AbilityComponent::AbilityComponent(Actor &actor)
    : m_Actor(actor)
{
}

inline std::span<const AbilityInstance> AbilityComponent::getAbilities() const
{
    return m_Abilities;
}

} // namespace checo::game