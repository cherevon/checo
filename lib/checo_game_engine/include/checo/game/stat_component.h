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
#include "checo/game/stat_definition.h"
#include "checo/game/unique_id.h"
#include "checo_game_engine_export.h"

#include <memory>
#include <span>

namespace checo::game
{

struct CHECO_GAME_ENGINE_EXPORT StatModifier
{
    enum Operation : uint8_t {
        kAdd = 0,
        kMultiply,
    };

    UniqueId m_SourceId{};

    Operation m_Operation{Operation::kAdd};
    float m_Value{0.0f};
};

class CHECO_GAME_ENGINE_EXPORT StatComponent : public ActorComponent
{
  public:
    static uint64_t getUniqueTypeId() { return 1792354019; }

  public:
    StatComponent();
    ~StatComponent() override;

  public:
    void addStat(const UniqueId statId, const float baseValue = 0.0f);
    void removeStat(const UniqueId statId);

    float getStatValue(const UniqueId statId) const;
    float getBaseStatValue(const UniqueId statId) const;
    void setBaseStatValue(const UniqueId statId, const float newBase);

    std::span<const StatModifier> getModifiers(const UniqueId statId) const;
    void addModifier(const UniqueId statId, const StatModifier &modifier);
    void removeModifiersBySourceId(const UniqueId sourceId);

  private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl{};
};

} // namespace checo::game