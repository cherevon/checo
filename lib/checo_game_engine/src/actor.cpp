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

#include "checo/game/actor.h"

#include <unordered_map>

namespace checo::game
{

using ActorComponentPtr = std::unique_ptr<ActorComponent, void (*)(ActorComponent *)>;

struct Actor::Impl
{
    std::unordered_map<uint64_t, ActorComponentPtr> m_Components{};
};

Actor::Actor(const UniqueId id)
    : m_Id{id},
      m_Impl{std::make_unique<Impl>()}
{
}

Actor::~Actor() = default;

ActorComponent *Actor::internalGetComponent(const uint64_t typeId)
{
    auto it = m_Impl->m_Components.find(typeId);
    if (it != m_Impl->m_Components.end()) {
        return it->second.get();
    }
    return nullptr;
}

bool Actor::internalAddComponent(const uint64_t typeId, ActorComponent *component, void (*deleter)(ActorComponent *))
{
    auto result = m_Impl->m_Components.emplace(typeId, ActorComponentPtr(component, deleter));
    return result.second;
}

void Actor::internalRemoveComponent(const uint64_t typeId)
{
    m_Impl->m_Components.erase(typeId);
}

} // namespace checo::game