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

#include "checo_rpg_test_support_export.h"

#include "checo/rpg/character.h"

#include <memory>

namespace checo::rpg::testing
{

CHECO_RPG_TEST_SUPPORT_EXPORT bool deepEqual(const Character &left, const Character &right);
CHECO_RPG_TEST_SUPPORT_EXPORT bool deepEqual(const CharacterStat &left, const CharacterStat &right);

CHECO_RPG_TEST_SUPPORT_EXPORT std::shared_ptr<Character> createTestCharacter(const UniqueId &id, const size_t statCount,
    const size_t itemCount, const size_t currencyCount, const size_t abilityCount, const size_t statusEffectCount);

} // namespace checo::rpg::testing
