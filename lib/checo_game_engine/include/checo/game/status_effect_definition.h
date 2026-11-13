/*
 * MIT License
 *
 * Copyright (c) 2024 Sergei Cherevichko
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

#include "checo/game/unique_id.h"
#include "checo/hash_map.h"
#include "checo/string.h"
#include "checo/variant.h"

#include <cstdint>

namespace checo::game
{

constexpr int STATUS_EFFECT_TYPE_BUFF = 0;
constexpr int STATUS_EFFECT_TYPE_DEBUFF = 1;

struct StatusEffectDefinition
{
    // Identity
    UniqueId m_Id{};
    int m_Type{STATUS_EFFECT_TYPE_BUFF};
    checo::String m_Name{};

    // UI
    checo::String m_DisplayName{};
    checo::String m_Description{};
    checo::String m_Icon{};

    // Custom properties
    checo::HashMap<checo::String, checo::Variant> m_Properties{};
};

} // namespace checo::game
