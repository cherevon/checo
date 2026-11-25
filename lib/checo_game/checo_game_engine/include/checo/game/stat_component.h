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

#include "checo/game/actor_component.h"
#include "checo/game/entity.h"
#include "checo/game/stat_definition.h"

#include <flat_map>
#include <span>
#include <vector>

namespace checo::game
{

struct StatModifier
{
    enum Operation : uint8_t {
        kFlatAdd = 0,
        kPercentAdd,
        kPercentMult,
    };

    EntityId m_SourceId{ENTITY_ID_INVALID};
    EntityType m_SourceType{ENTITY_TYPE_NONE};
    Operation m_Operation{Operation::kFlatAdd};
    float m_Value{0.0f};
};

class StatComponent : public ActorComponent
{
  public:
    static uint64_t getUniqueTypeId() { return 1792354019; }

  public:
    StatComponent() = default;
    ~StatComponent() override = default;

  public:
    void addStat(EntityId statId, float baseValue = 0.0f);
    void removeStat(EntityId statId);

    float getStatValue(EntityId statId) const;
    float getBaseStatValue(EntityId statId) const;
    void setBaseStatValue(EntityId statId, float newBase);

    std::span<const StatModifier> getModifiers(EntityId statId) const;
    void addModifier(EntityId statId, const StatModifier &modifier);
    void removeModifiersBySourceId(EntityId sourceId, EntityType sourceType);

  private:
    struct Stat
    {
        float m_BaseValue{0.0f};
        float m_CurrentValue{0.0f};
        std::vector<StatModifier> m_Modifiers{};
    };

  private:
    void calculateStat(Stat &stat);

  private:
    std::flat_map<EntityId, Stat> m_Stats{};
};

} // namespace checo::game