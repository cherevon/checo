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

#include "checo/game/tag_component.h"

#include <string_view>
#include <unordered_set>

namespace checo::game
{

struct TagComponent::Impl
{
    std::unordered_set<uint64_t> m_TagHashes{};
};

TagComponent::TagComponent()
    : m_Impl(std::make_unique<Impl>())
{
}

TagComponent::~TagComponent() = default;

void TagComponent::addTag(const std::string_view tag)
{
    const uint64_t tagHash = std::hash<std::string_view>{}(tag);
    m_Impl->m_TagHashes.insert(tagHash);
}

bool TagComponent::hasTag(const std::string_view tag) const
{
    const uint64_t tagHash = std::hash<std::string_view>{}(tag);
    return m_Impl->m_TagHashes.find(tagHash) != m_Impl->m_TagHashes.end();
}

void TagComponent::removeTag(const std::string_view tag)
{
    const uint64_t tagHash = std::hash<std::string_view>{}(tag);
    m_Impl->m_TagHashes.erase(tagHash);
}

void TagComponent::clearTags()
{
    m_Impl->m_TagHashes.clear();
}

} // namespace checo::game