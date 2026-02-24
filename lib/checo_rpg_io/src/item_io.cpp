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

#include "checo/rpg/item_io.h"
#include "checo/rpg/entity_io.h"

#include "checo/vector_io.h"

namespace checo::rpg
{

using AbilityReader = std::function<std::shared_ptr<Ability>(std::istream &)>;
using AbilityWriter = std::function<void(std::ostream &, const std::shared_ptr<Ability> &)>;

using StatusEffectReader = std::function<std::shared_ptr<StatusEffect>(std::istream &)>;
using StatusEffectWriter = std::function<void(std::ostream &, const std::shared_ptr<StatusEffect> &)>;

void readBinary(std::istream &inStream, Item &data, AbilityReader readAbilityFunc,
    StatusEffectReader readStatusEffectFunc)
{
    // Read entity data
    readBinary(inStream, static_cast<Entity &>(data));

    // Read abilities
    checo::readBinary(inStream, data.m_Abilities,
        [&readAbilityFunc](std::istream &stream, std::shared_ptr<Ability> &ability)
        { ability = readAbilityFunc(stream); });

    // Read status effects
    checo::readBinary(inStream, data.m_StatusEffects,
        [&readStatusEffectFunc](std::istream &stream, std::shared_ptr<StatusEffect> &statusEffect)
        { statusEffect = readStatusEffectFunc(stream); });
}

void writeBinary(std::ostream &outStream, const Item &data, AbilityWriter writeFunc,
    StatusEffectWriter statusEffectWriteFunc)
{
    // Write entity data
    writeBinary(outStream, static_cast<const Entity &>(data));

    // Write abilities
    checo::writeBinary(outStream, data.m_Abilities,
        [&writeFunc](std::ostream &stream, const std::shared_ptr<Ability> &ability) { writeFunc(stream, ability); });

    // Write status effects
    checo::writeBinary(outStream, data.m_StatusEffects,
        [&statusEffectWriteFunc](std::ostream &stream, const std::shared_ptr<StatusEffect> &statusEffect)
        { statusEffectWriteFunc(stream, statusEffect); });
}

} // namespace checo::rpg