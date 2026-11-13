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
#include "checo/game/unique_id.h"
#include "checo_game_engine_export.h"

#include <cstdint>
#include <memory>

namespace checo::game
{

class CHECO_GAME_ENGINE_EXPORT Actor
{
  public:
    explicit Actor(const UniqueId id);
    virtual ~Actor();

  public:
    Actor(const Actor &) = delete;
    Actor &operator=(const Actor &) = delete;

  public:
    template <ActorComponentType T>
    T *getComponent()
    {
        return static_cast<T *>(internalGetComponent(T::getUniqueTypeId()));
    }

    template <ActorComponentType T, typename... Args>
    bool addComponent(Args &&...args)
    {
        // Pass custom deleter to make sure the component is created and deleted correctly across DLL boundaries (in the
        // same heap)
        ActorComponent *component = new T(std::forward<Args>(args)...);
        auto deleter = [](ActorComponent *ptr) { delete ptr; };
        return internalAddComponent(T::getUniqueTypeId(), component, deleter);
    }

    template <ActorComponentType T>
    void removeComponent()
    {
        internalRemoveComponent(T::getUniqueTypeId());
    }

  public:
    UniqueId getId() const noexcept;
    void setId(const UniqueId id) noexcept;

  private:
    ActorComponent *internalGetComponent(const uint64_t typeId);
    bool internalAddComponent(const uint64_t typeId, ActorComponent *component, void (*deleter)(ActorComponent *));
    void internalRemoveComponent(const uint64_t typeId);

  private:
    UniqueId m_Id{};

    struct Impl;
    std::unique_ptr<Impl> m_Impl;
};

inline UniqueId Actor::getId() const noexcept
{
    return m_Id;
}

inline void Actor::setId(const UniqueId id) noexcept
{
    m_Id = id;
}

} // namespace checo::game