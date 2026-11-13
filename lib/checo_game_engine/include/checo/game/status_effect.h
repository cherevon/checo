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
#include "checo/game/unique_id.h"
#include "checo_game_engine_export.h"

#include <memory>

namespace checo::game
{

class CHECO_GAME_ENGINE_EXPORT StatusEffect
{
  public:
    explicit StatusEffect(const UniqueId instanceId = {}, const UniqueId definitionId = {},
        const UniqueId sourceId = {}) noexcept;
    virtual ~StatusEffect();

  public:
    StatusEffect(const StatusEffect &other) = delete;
    StatusEffect &operator=(const StatusEffect &other) = delete;

    StatusEffect(StatusEffect &&other) = delete;
    StatusEffect &operator=(StatusEffect &&other) = delete;

  public:
    UniqueId getInstanceId() const noexcept;
    void setInstanceId(const UniqueId instanceId) noexcept;

    UniqueId getDefinitionId() const noexcept;
    void setDefinitionId(const UniqueId definitionId) noexcept;

    UniqueId getSourceId() const noexcept;
    void setSourceId(const UniqueId sourceId) noexcept;

    virtual void apply(Actor *target) = 0;
    virtual void remove(Actor *target) = 0;

  private:
    UniqueId m_InstanceId{};
    UniqueId m_DefinitionId{};
    UniqueId m_SourceId{};
};

inline UniqueId StatusEffect::getInstanceId() const noexcept
{
    return m_InstanceId;
}

inline void StatusEffect::setInstanceId(const UniqueId instanceId) noexcept
{
    m_InstanceId = instanceId;
}

inline UniqueId StatusEffect::getDefinitionId() const noexcept
{
    return m_DefinitionId;
}

inline void StatusEffect::setDefinitionId(const UniqueId definitionId) noexcept
{
    m_DefinitionId = definitionId;
}

inline UniqueId StatusEffect::getSourceId() const noexcept
{
    return m_SourceId;
}

inline void StatusEffect::setSourceId(const UniqueId sourceId) noexcept
{
    m_SourceId = sourceId;
}

} // namespace checo::game