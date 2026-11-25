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

namespace checo::game
{

void StatComponent::addStat(EntityId statId, float baseValue)
{
    auto statIter = m_Stats.find(statId);
    if (statIter == m_Stats.end()) {
        m_Stats[statId] = Stat{
            .m_BaseValue = baseValue,
            .m_CurrentValue = baseValue,
        };
    } else { // Stat already exists
        statIter->second.m_BaseValue = baseValue;
        calculateStat(statIter->second);
    }
}

void StatComponent::removeStat(EntityId statId)
{
    m_Stats.erase(statId);
}

float StatComponent::getStatValue(EntityId statId) const
{
    auto statIter = m_Stats.find(statId);
    if (statIter == m_Stats.end()) {
        return 0.0f;
    }
    return statIter->second.m_CurrentValue;
}

float StatComponent::getBaseStatValue(EntityId statId) const
{
    const auto statIter = m_Stats.find(statId);
    if (statIter == m_Stats.end()) {
        return 0.0f;
    }

    return statIter->second.m_BaseValue;
}

void StatComponent::setBaseStatValue(EntityId statId, float newBase)
{
    auto statIter = m_Stats.find(statId);
    if (statIter == m_Stats.end() || statIter->second.m_BaseValue == newBase) {
        return;
    }

    statIter->second.m_BaseValue = newBase;
    calculateStat(statIter->second);
}

std::span<const StatModifier> StatComponent::getModifiers(EntityId statId) const
{
    const auto statIter = m_Stats.find(statId);
    if (statIter == m_Stats.end()) {
        return {};
    }

    return statIter->second.m_Modifiers;
}

void StatComponent::addModifier(EntityId statId, const StatModifier &modifier)
{
    auto statIter = m_Stats.find(statId);
    if (statIter == m_Stats.end()) {
        return;
    }

    statIter->second.m_Modifiers.push_back(modifier);
    calculateStat(statIter->second);
}

void StatComponent::removeModifiersBySourceId(EntityId sourceId, EntityType sourceType)
{
    for (auto [statId, stat] : m_Stats) {
        const auto delCount = std::erase_if(stat.m_Modifiers,
            [&](const StatModifier &mod) { return mod.m_SourceType == sourceType && mod.m_SourceId == sourceId; });
        if (delCount > 0) {
            calculateStat(stat);
        }
    }
}

void StatComponent::calculateStat(Stat &stat)
{
    float flatAdd = 0.0f;
    float percentAdd = 0.0f;
    float percentMult = 1.0f;

    for (const auto &mod : stat.m_Modifiers) {
        switch (mod.m_Operation) {
        case StatModifier::kFlatAdd:
            flatAdd += mod.m_Value;
            break;
        case StatModifier::kPercentAdd: // for example, 0.2f for +20%
            percentAdd += mod.m_Value;
            break;
        case StatModifier::kPercentMult: // for example, 1.5f for x1.5
            percentMult *= mod.m_Value;
            break;
        }
    }

    stat.m_CurrentValue = (stat.m_BaseValue + flatAdd) * (1.0f + percentAdd) * percentMult;
}

} // namespace checo::game