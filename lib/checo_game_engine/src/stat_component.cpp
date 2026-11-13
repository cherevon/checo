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

#include "checo/game/stat_component.h"

#include <unordered_map>
#include <vector>

namespace checo::game
{

struct Stat
{
    float m_BaseValue{0.0f};
    float m_CurrentValue{0.0f};
    bool m_IsDirty{false};

    std::vector<StatModifier> m_Modifiers{};
};

struct StatComponent::Impl
{
    std::unordered_map<UniqueId, Stat> m_Stats{};
};

StatComponent::StatComponent()
    : m_Impl(std::make_unique<Impl>())
{
}

StatComponent::~StatComponent() = default;

void StatComponent::addStat(const UniqueId statId, const float baseValue)
{
    auto statIter = m_Impl->m_Stats.find(statId);
    if (statIter == m_Impl->m_Stats.end()) {
        m_Impl->m_Stats[statId] = Stat{
            .m_BaseValue = baseValue,
            .m_CurrentValue = baseValue,
            .m_IsDirty = false,
        };
    } else { // Stat already exists
        statIter->second.m_BaseValue = baseValue;
        statIter->second.m_IsDirty = true;
    }
}

void StatComponent::removeStat(const UniqueId statId)
{
    m_Impl->m_Stats.erase(statId);
}

float StatComponent::getStatValue(const UniqueId statId) const
{
    const auto statIter = m_Impl->m_Stats.find(statId);
    if (statIter == m_Impl->m_Stats.end()) {
        return 0.0f;
    }

    if (statIter->second.m_IsDirty) {
        // Recalculate the current value based on the base value and modifiers
        float newValue = statIter->second.m_BaseValue;
        for (const auto &modifier : statIter->second.m_Modifiers) {
            switch (modifier.m_Operation) {
            case StatModifier::kAdd:
                newValue += modifier.m_Value;
                break;
            case StatModifier::kMultiply:
                newValue *= modifier.m_Value;
                break;
            default:
                // Unknown operation, do nothing
                break;
            }
        }
        statIter->second.m_CurrentValue = newValue;
        statIter->second.m_IsDirty = false;
    }
    return statIter->second.m_CurrentValue;
}

float StatComponent::getBaseStatValue(const UniqueId statId) const
{
    const auto statIter = m_Impl->m_Stats.find(statId);
    if (statIter == m_Impl->m_Stats.end()) {
        return 0.0f;
    }

    return statIter->second.m_BaseValue;
}

void StatComponent::setBaseStatValue(const UniqueId statId, const float newBase)
{
    auto statIter = m_Impl->m_Stats.find(statId);
    if (statIter == m_Impl->m_Stats.end()) {
        return;
    }

    statIter->second.m_BaseValue = newBase;
    statIter->second.m_IsDirty = true;
}

std::span<const StatModifier> StatComponent::getModifiers(const UniqueId statId) const
{
    const auto statIter = m_Impl->m_Stats.find(statId);
    if (statIter == m_Impl->m_Stats.end()) {
        return {};
    }

    return statIter->second.m_Modifiers;
}

void StatComponent::addModifier(const UniqueId statId, const StatModifier &modifier)
{
    auto statIter = m_Impl->m_Stats.find(statId);
    if (statIter == m_Impl->m_Stats.end()) {
        return;
    }

    statIter->second.m_Modifiers.push_back(modifier);
    statIter->second.m_IsDirty = true;
}

void StatComponent::removeModifiersBySourceId(const UniqueId sourceId)
{
    for (auto &[statId, stat] : m_Impl->m_Stats) {
        auto &modifiers = stat.m_Modifiers;

        const auto delCount =
            std::erase_if(modifiers, [&](const StatModifier &mod) { return mod.m_SourceId == sourceId; });
        if (delCount > 0) {
            stat.m_IsDirty = true;
        }
    }
}

} // namespace checo::game