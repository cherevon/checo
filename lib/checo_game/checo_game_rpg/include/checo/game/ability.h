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
#include "checo/game/entity.h"

#include <functional>

namespace checo::game
{

class Ability;

struct AbilityInstance
{
  public:
    std::reference_wrapper<Ability> m_Ability;

    EntityId m_InstanceId{ENTITY_ID_INVALID};
    EntityId m_DefinitionId{ENTITY_ID_INVALID};
    EntityId m_SourceId{ENTITY_ID_INVALID};
    EntityType m_SourceType{ENTITY_TYPE_NONE};

    void *m_UserData{nullptr};
};

class Ability
{
  public:
    Ability() noexcept = default;
    virtual ~Ability() = default;

  public:
    Ability(const Ability &other) = delete;
    Ability &operator=(const Ability &other) = delete;

    Ability(Ability &&other) = delete;
    Ability &operator=(Ability &&other) = delete;

  public:
    virtual void cast(Actor &source, Actor &target, AbilityInstance &instance) = 0;
};

} // namespace checo::game