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

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace checo::game
{

class Actor
{
  public:
    explicit Actor(const EntityId id);
    virtual ~Actor() = default;

  public:
    Actor(const Actor &) = delete;
    Actor &operator=(const Actor &) = delete;

  public:
    template <ActorComponentType T>
    T *getComponent();

    template <ActorComponentType T, typename... Args>
    void addComponent(Args &&...args);

    template <ActorComponentType T>
    void removeComponent();

  public:
    EntityId getId() const noexcept;
    void setId(const EntityId id) noexcept;

  private:
    EntityId m_Id{};
    std::unordered_map<uint64_t, std::unique_ptr<ActorComponent>> m_Components{};
};

inline Actor::Actor(const EntityId id)
    : m_Id{id}
{
}

template <ActorComponentType T>
T *Actor::getComponent()
{
    auto it = m_Components.find(T::getUniqueTypeId());
    if (it != m_Components.end()) {
        return static_cast<T *>(it->second.get());
    }
    return nullptr;
}

template <ActorComponentType T, typename... Args>
void Actor::addComponent(Args &&...args)
{
    m_Components[T::getUniqueTypeId()] = std::make_unique<T>(std::forward<Args>(args)...);
}

template <ActorComponentType T>
void Actor::removeComponent()
{
    m_Components.erase(T::getUniqueTypeId());
}

inline EntityId Actor::getId() const noexcept
{
    return m_Id;
}

inline void Actor::setId(const EntityId id) noexcept
{
    m_Id = id;
}

} // namespace checo::game