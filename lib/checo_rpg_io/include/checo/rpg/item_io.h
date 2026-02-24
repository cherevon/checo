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

#include "checo_rpg_io_export.h"

#include "checo/rpg/item.h"

#include <functional>
#include <iostream>
#include <memory>

namespace checo::rpg
{

void CHECO_RPG_IO_EXPORT readBinary(std::istream &inStream, Item &data,
    const std::function<std::shared_ptr<Ability>(std::istream &)> &readAbilityFunc,
    const std::function<std::shared_ptr<StatusEffect>(std::istream &)> &readStatusEffectFunc);
void CHECO_RPG_IO_EXPORT writeBinary(std::ostream &outStream, const Item &data,
    const std::function<void(std::ostream &, const std::shared_ptr<Ability> &)> &writeAbilityFunc,
    const std::function<void(std::ostream &, const std::shared_ptr<StatusEffect> &)> &writeStatusEffectFunc);

} // namespace checo::rpg