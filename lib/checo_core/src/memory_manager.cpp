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

#include "checo/memory_manager.h"

#include <cstdlib>
#include <new>
#include <unordered_map>

namespace checo
{

struct Allocation
{
    size_t m_Size{0};
    size_t m_Alignment{0};
};

static std::unordered_map<void *, Allocation> m_Allocations{};

void *allocate(const size_t size, const size_t alignment)
{
    const size_t useAlignment = alignment == 0 ? alignof(std::max_align_t) : alignment;
    void *ptr = ::operator new(size, std::align_val_t(useAlignment));
    try {
        m_Allocations[ptr] = Allocation{size, useAlignment};
    } catch (...) {
        ::operator delete(ptr, std::align_val_t(useAlignment));
        throw;
    }
    return ptr;
}

void deallocate(void *ptr) noexcept
{
    // Nothing to deallocate if we didn't allocate anything for this pointer
    const auto allocIter = m_Allocations.find(ptr);
    if (allocIter == m_Allocations.end()) {
        return;
    }

    // Deallocate the memory using the stored alignment
    ::operator delete(ptr, std::align_val_t(allocIter->second.m_Alignment));
    m_Allocations.erase(allocIter);
}

size_t getTotalAllocated() noexcept
{
    size_t total = 0;
    for (const auto &alloc : m_Allocations) {
        total += alloc.second.m_Size;
    }
    return total;
}

} // namespace checo