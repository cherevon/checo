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

#include "checo/rpg/ability.h"
#include "checo/rpg/entity.h"
#include "checo/rpg/inventory.h"
#include "checo/rpg/stat.h"
#include "checo/rpg/status_effect.h"
#include "checo_rpg_export.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace checo::rpg
{

struct CHECO_RPG_EXPORT CharacterStat
{
  public:
    std::shared_ptr<Stat> m_Stat{};
    int8_t m_Value{0};
};

struct CHECO_RPG_EXPORT Character : public Entity
{
  public:
    std::vector<CharacterStat> m_Stats{};
    Inventory m_Inventory{};
    std::vector<std::shared_ptr<Ability>> m_Abilities{};
    std::vector<std::shared_ptr<StatusEffect>> m_StatusEffects{};
};

} // namespace checo::rpg
