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

#include "checo_game_engine_export.h"

#include <concepts>
#include <cstdint>

namespace checo::game
{

class CHECO_GAME_ENGINE_EXPORT ActorComponent
{
  public:
    virtual ~ActorComponent();

    ActorComponent(const ActorComponent &) = delete;
    ActorComponent &operator=(const ActorComponent &) = delete;
    ActorComponent(ActorComponent &&) = delete;
    ActorComponent &operator=(ActorComponent &&) = delete;

  protected:
    ActorComponent();
};

template <typename T>
concept ActorComponentType = requires(const T &) {
    std::derived_from<T, ActorComponent>;
    { T::getUniqueTypeId() } -> std::convertible_to<uint64_t>; // Use UTC time in seconds as the unique type ID
};

} // namespace checo::game