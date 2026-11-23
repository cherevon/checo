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

#include "checo/game/status_effect_component.h"

#include <algorithm>
#include <functional>

namespace checo::game
{

EntityId StatusEffectComponent::addEffect(const StatusEffectInstance &effectInstance)
{
    // Add the effect to the list and assign it a unique instance ID
    auto &newEffectInstance = m_Effects.emplace_back(effectInstance);
    newEffectInstance.m_InstanceId = m_NextInstanceId++;

    // Apply the effect to the actor
    newEffectInstance.m_Effect.get().apply(m_Actor, newEffectInstance);

    // Return newly assigned instance ID
    return newEffectInstance.m_InstanceId;
}

void StatusEffectComponent::removeEffect(const EntityId instanceId)
{
    // Find the effect to be removed
    const auto effectIter = std::find_if(m_Effects.begin(), m_Effects.end(),
        [&](const auto &effect) { return effect.m_InstanceId == instanceId; });
    if (effectIter == m_Effects.end()) {
        return;
    }

    // Take effect ownership before erasing it from the list (recursion safety)
    auto effectToRemove = std::move(*effectIter);
    m_Effects.erase(effectIter);

    // Revoke the impact of the effect on the actor
    effectToRemove.m_Effect.get().remove(m_Actor, effectToRemove);
}

void StatusEffectComponent::removeEffectsByDefinitionId(const EntityId definitionId)
{
    // Take ownership of effects to be removed before erasing them (recursion safety)
    std::vector<StatusEffectInstance> effectsToRemove;
    std::erase_if(m_Effects, [&](auto &effect) {
        if (effect.m_DefinitionId == definitionId) {
            effectsToRemove.push_back(std::move(effect));
            return true;
        }
        return false;
    });

    // Revoke the impact of the removed effects on the actor
    for (auto &effectInst : effectsToRemove) {
        effectInst.m_Effect.get().remove(m_Actor, effectInst);
    }
}

void StatusEffectComponent::removeEffectsBySourceId(const EntityId sourceId)
{
    // Take ownership of effects to be removed before erasing them (recursion safety)
    std::vector<StatusEffectInstance> effectsToRemove;
    std::erase_if(m_Effects, [&](auto &effect) {
        if (effect.m_SourceId == sourceId) {
            effectsToRemove.push_back(std::move(effect));
            return true;
        }
        return false;
    });

    // Revoke the impact of the removed effects on the actor
    for (auto &effectInst : effectsToRemove) {
        effectInst.m_Effect.get().remove(m_Actor, effectInst);
    }
}

bool StatusEffectComponent::hasEffect(const EntityId instanceId) const
{
    return std::ranges::any_of(m_Effects, std::bind_front(std::equal_to{}, instanceId),
        &StatusEffectInstance::m_InstanceId);
}

bool StatusEffectComponent::hasEffectByDefinitionId(const EntityId definitionId) const
{
    return std::ranges::any_of(m_Effects, std::bind_front(std::equal_to{}, definitionId),
        &StatusEffectInstance::m_DefinitionId);
}

bool StatusEffectComponent::hasEffectBySourceId(const EntityId sourceId) const
{
    return std::ranges::any_of(m_Effects, std::bind_front(std::equal_to{}, sourceId),
        &StatusEffectInstance::m_SourceId);
}

void StatusEffectComponent::clearEffects()
{
    // Take ownership of all effects before clearing them (recursion safety)
    std::vector<StatusEffectInstance> effectsToRemove;
    effectsToRemove.swap(m_Effects);

    // Revoke the impact of all effects on the actor before clearing them
    for (auto &effectInst : effectsToRemove) {
        effectInst.m_Effect.get().remove(m_Actor, effectInst);
    }
}

} // namespace checo::game