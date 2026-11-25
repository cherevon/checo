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

void StatusEffectComponent::addEffect(const StatusEffectInstance &effectInstance)
{
    auto &newEffectInstance = m_Effects.emplace_back(effectInstance);
    newEffectInstance.m_Effect.get().apply(m_Actor, newEffectInstance);
}

void StatusEffectComponent::removeEffect(EntityId instanceId)
{
    // Take ownership of effects to be removed before erasing them (recursion safety)
    std::vector<StatusEffectInstance> effectsToRemove;
    std::erase_if(m_Effects, [&](auto &effect) {
        if (effect.m_InstanceId == instanceId) {
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

void StatusEffectComponent::removeEffectsByDefinitionId(EntityId definitionId)
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

void StatusEffectComponent::removeEffectsBySourceId(EntityId sourceId, EntityType sourceType)
{
    // Take ownership of effects to be removed before erasing them (recursion safety)
    std::vector<StatusEffectInstance> effectsToRemove;
    std::erase_if(m_Effects, [&](auto &effect) {
        if (effect.m_SourceType == sourceType && effect.m_SourceId == sourceId) {
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

bool StatusEffectComponent::hasEffect(EntityId instanceId) const
{
    return std::ranges::any_of(m_Effects, std::bind_front(std::equal_to{}, instanceId),
        &StatusEffectInstance::m_InstanceId);
}

bool StatusEffectComponent::hasEffectByDefinitionId(EntityId definitionId) const
{
    return std::ranges::any_of(m_Effects, std::bind_front(std::equal_to{}, definitionId),
        &StatusEffectInstance::m_DefinitionId);
}

bool StatusEffectComponent::hasEffectBySourceId(EntityId sourceId, EntityType sourceType) const
{
    return std::ranges::any_of(m_Effects, [&](const StatusEffectInstance &effect) {
        return effect.m_SourceType == sourceType && effect.m_SourceId == sourceId;
    });
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