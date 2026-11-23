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

#include "checo/game/actor.h"
#include "checo/game/actor_component.h"
#include "checo/game/entity.h"
#include "checo/game/status_effect.h"

#include <cstdint>
#include <memory>
#include <span>
#include <vector>

namespace checo::game
{

class StatusEffectComponent : public ActorComponent
{
  public:
    static uint64_t getUniqueTypeId() { return 1792537580; }

  public:
    explicit StatusEffectComponent(Actor &actor);
    ~StatusEffectComponent() override = default;

  public:
    std::span<const StatusEffectInstance> getEffects() const;

    EntityId addEffect(const StatusEffectInstance &effectInstance);

    void removeEffect(const EntityId instanceId);
    void removeEffectsByDefinitionId(const EntityId definitionId);
    void removeEffectsBySourceId(const EntityId sourceId);

    bool hasEffect(const EntityId instanceId) const;
    bool hasEffectByDefinitionId(const EntityId definitionId) const;
    bool hasEffectBySourceId(const EntityId sourceId) const;

    void clearEffects();

  private:
    Actor &m_Actor;
    std::vector<StatusEffectInstance> m_Effects{};
    EntityId m_NextInstanceId{1};
};

inline StatusEffectComponent::StatusEffectComponent(Actor &actor)
    : m_Actor(actor)
{
}

inline std::span<const StatusEffectInstance> StatusEffectComponent::getEffects() const
{
    return m_Effects;
}

} // namespace checo::game