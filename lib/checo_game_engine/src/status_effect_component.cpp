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
#include <vector>

namespace checo::game
{

struct StatusEffectComponent::Impl
{
    Actor *m_Actor{nullptr};
    std::vector<std::shared_ptr<StatusEffect>> m_Effects;
};

StatusEffectComponent::StatusEffectComponent(Actor *actor)
    : m_Impl(std::make_unique<Impl>())
{
    m_Impl->m_Actor = actor;
}

StatusEffectComponent::~StatusEffectComponent() = default;

void StatusEffectComponent::forEachEffect(void (*callback)(const StatusEffect *effect))
{
    for (const auto &effect : m_Impl->m_Effects) {
        callback(effect.get());
    }
}

void StatusEffectComponent::addEffect(std::shared_ptr<StatusEffect> effect)
{
    m_Impl->m_Effects.push_back(std::move(effect));
    m_Impl->m_Effects.back()->apply(m_Impl->m_Actor);
}

void StatusEffectComponent::removeEffect(const UniqueId instanceId)
{
    std::erase_if(m_Impl->m_Effects, [&](const auto &effect) {
        if (effect->getInstanceId() == instanceId) {
            effect->remove(m_Impl->m_Actor);
            return true;
        }
        return false;
    });
}

void StatusEffectComponent::removeEffectsByDefinitionId(const UniqueId definitionId)
{

    std::erase_if(m_Impl->m_Effects, [&](const auto &effect) {
        if (effect->getDefinitionId() == definitionId) {
            effect->remove(m_Impl->m_Actor);
            return true;
        }
        return false;
    });
}

void StatusEffectComponent::removeEffectsBySourceId(const UniqueId sourceId)
{
    std::erase_if(m_Impl->m_Effects, [&](const auto &effect) {
        if (effect->getSourceId() == sourceId) {
            effect->remove(m_Impl->m_Actor);
            return true;
        }
        return false;
    });
}

bool StatusEffectComponent::hasEffect(const UniqueId instanceId) const
{
    return std::ranges::any_of(m_Impl->m_Effects, std::bind_front(std::equal_to{}, instanceId),
        &StatusEffect::getInstanceId);
}

bool StatusEffectComponent::hasEffectByDefinitionId(const UniqueId definitionId) const
{
    return std::ranges::any_of(m_Impl->m_Effects, std::bind_front(std::equal_to{}, definitionId),
        &StatusEffect::getDefinitionId);
}

bool StatusEffectComponent::hasEffectBySourceId(const UniqueId sourceId) const
{
    return std::ranges::any_of(m_Impl->m_Effects, std::bind_front(std::equal_to{}, sourceId),
        &StatusEffect::getSourceId);
}

void StatusEffectComponent::clearEffects()
{
    for (auto &effect : m_Impl->m_Effects) {
        effect->remove(m_Impl->m_Actor);
    }
    m_Impl->m_Effects.clear();
}

} // namespace checo::game