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

#include "checo/rpg/character_io.h"
#include "checo/rpg/entity_io.h"

#include "checo/fundamental_io.h"
#include "checo/vector_io.h"

namespace checo::rpg
{

using StatReader = std::function<std::shared_ptr<Stat>(std::istream &)>;
using StatWriter = std::function<void(std::ostream &, const std::shared_ptr<Stat> &)>;

using InventoryReader = std::function<std::shared_ptr<Inventory>(std::istream &)>;
using InventoryWriter = std::function<void(std::ostream &, const std::shared_ptr<Inventory> &)>;

using AbilityReader = std::function<std::shared_ptr<Ability>(std::istream &)>;
using AbilityWriter = std::function<void(std::ostream &, const std::shared_ptr<Ability> &)>;

using StatusEffectReader = std::function<std::shared_ptr<StatusEffect>(std::istream &)>;
using StatusEffectWriter = std::function<void(std::ostream &, const std::shared_ptr<StatusEffect> &)>;

void readBinary(std::istream &inStream, CharacterStat &data, const StatReader &readStatFunc)
{
    // Read stat
    data.m_Stat = readStatFunc(inStream);

    // Read value
    checo::readBinary(inStream, data.m_Value);
}

void writeBinary(std::ostream &outStream, const CharacterStat &data, const StatWriter &writeStatFunc)
{
    // Write stat
    writeStatFunc(outStream, data.m_Stat);

    // Write value
    checo::writeBinary(outStream, data.m_Value);
}

void readBinary(std::istream &inStream, Character &data, const StatReader &readStatFunc,
    const InventoryReader &readInventoryFunc, const AbilityReader &readAbilityFunc,
    const StatusEffectReader &readStatusEffectFunc)
{
    // Read entity data
    readBinary(inStream, static_cast<Entity &>(data));

    // Read stats
    const auto readStatFuncWrapper = [&](std::istream &stream, CharacterStat &charStat) {
        readBinary(stream, charStat, readStatFunc);
    };
    checo::readBinary(inStream, data.m_Stats, readStatFuncWrapper);

    // Read inventory
    data.m_Inventory = readInventoryFunc(inStream);

    // Read abilities
    const auto readAbilityFuncWrapper = [&](std::istream &stream, std::shared_ptr<Ability> &ability) {
        ability = readAbilityFunc(stream);
    };
    checo::readBinary(inStream, data.m_Abilities, readAbilityFuncWrapper);

    // Read status effects
    const auto readStatusEffectFuncWrapper = [&](std::istream &stream, std::shared_ptr<StatusEffect> &statusEffect) {
        statusEffect = readStatusEffectFunc(stream);
    };
    checo::readBinary(inStream, data.m_StatusEffects, readStatusEffectFuncWrapper);
}

void writeBinary(std::ostream &outStream, const Character &data, const StatWriter &writeStatFunc,
    const InventoryWriter &writeInventoryFunc, const AbilityWriter &writeAbilityFunc,
    const StatusEffectWriter &writeStatusEffectFunc)
{
    // Write entity data
    writeBinary(outStream, static_cast<const Entity &>(data));

    // Write stats
    const auto writeStatFuncWrapper = [&](std::ostream &stream, const CharacterStat &charStat) {
        writeBinary(stream, charStat, writeStatFunc);
    };
    checo::writeBinary(outStream, data.m_Stats, writeStatFuncWrapper);

    // Write inventory
    writeInventoryFunc(outStream, data.m_Inventory);

    // Write abilities
    const auto writeAbilityFuncWrapper = [&](std::ostream &stream, const std::shared_ptr<Ability> &ability) {
        writeAbilityFunc(stream, ability);
    };
    checo::writeBinary(outStream, data.m_Abilities, writeAbilityFuncWrapper);

    // Write status effects
    const auto writeStatusEffectFuncWrapper = [&](std::ostream &stream,
                                                  const std::shared_ptr<StatusEffect> &statusEffect) {
        writeStatusEffectFunc(stream, statusEffect);
    };
    checo::writeBinary(outStream, data.m_StatusEffects, writeStatusEffectFuncWrapper);
}

} // namespace checo::rpg