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
#include "checo/game/status_effect.h"
#include "checo/game/unique_id.h"
#include "checo_game_engine_export.h"

#include <cstdint>
#include <memory>

namespace checo::game
{

class CHECO_GAME_ENGINE_EXPORT StatusEffectComponent : public ActorComponent
{
  public:
    static uint64_t getUniqueTypeId() { return 1792537580; }

  public:
    explicit StatusEffectComponent(Actor *actor);
    ~StatusEffectComponent() override;

  public:
    void forEachEffect(void (*callback)(const StatusEffect *effect));

    void addEffect(std::shared_ptr<StatusEffect> effect);

    void removeEffect(const UniqueId instanceId);
    void removeEffectsByDefinitionId(const UniqueId definitionId);
    void removeEffectsBySourceId(const UniqueId sourceId);

    bool hasEffect(const UniqueId instanceId) const;
    bool hasEffectByDefinitionId(const UniqueId definitionId) const;
    bool hasEffectBySourceId(const UniqueId sourceId) const;

    void clearEffects();

  private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl{};
};

} // namespace checo::game