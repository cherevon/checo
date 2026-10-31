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
#include "checo/vector.h"

#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <utility>

namespace checo::testing
{

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

template <typename T>
T makeValue(int seed);

template <>
int makeValue<int>(int seed)
{
    return seed * 7;
}

template <>
double makeValue<double>(int seed)
{
    return seed * 1.5;
}

template <>
std::string makeValue<std::string>(int seed)
{
    // 32 chars to exceed SSO on most platforms so that the string's own
    // heap allocation does not interfere with checo::getTotalAllocated(),
    // which only tracks memory routed through checo::allocate.
    return std::string(32, static_cast<char>('a' + seed % 26));
}

// ---------------------------------------------------------------------------
// Typed fixture
// ---------------------------------------------------------------------------

template <typename T>
class VectorTest : public ::testing::Test
{
};

using TestTypes = ::testing::Types<int, double, std::string>;
TYPED_TEST_SUITE(VectorTest, TestTypes);

// ===========================================================================
// Default constructor
// ===========================================================================

TYPED_TEST(VectorTest, DefaultConstructor_NoAllocation)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
        EXPECT_EQ(checo::getTotalAllocated(), before);
        EXPECT_EQ(v.size(), 0u);
        EXPECT_EQ(v.capacity(), 0u);
        EXPECT_TRUE(v.empty());
        EXPECT_EQ(v.data(), nullptr);
        EXPECT_EQ(v.begin(), nullptr);
        EXPECT_EQ(v.end(), nullptr);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

// ===========================================================================
// Capacity constructor  Vector(size_t)
// ===========================================================================

TYPED_TEST(VectorTest, CapacityConstructor_AllocatesExactly)
{
    constexpr size_t cap = 8;
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v(cap);
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * cap);
        EXPECT_EQ(v.size(), 0u);
        EXPECT_EQ(v.capacity(), cap);
        EXPECT_TRUE(v.empty());
        EXPECT_NE(v.data(), nullptr);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, CapacityConstructor_ZeroNoAllocation)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v(0u);
        EXPECT_EQ(checo::getTotalAllocated(), before);
        EXPECT_EQ(v.size(), 0u);
        EXPECT_EQ(v.capacity(), 0u);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

// ===========================================================================
// Count-fill constructor  Vector(size_t, const T&)
// ===========================================================================

TYPED_TEST(VectorTest, CountFillConstructor_AllocatesExactly)
{
    constexpr size_t count = 5;
    const TypeParam fill = makeValue<TypeParam>(3);
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v(count, fill);
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * count);
        EXPECT_EQ(v.size(), count);
        EXPECT_EQ(v.capacity(), count);
        EXPECT_FALSE(v.empty());
        for (size_t i = 0; i < count; ++i)
            EXPECT_EQ(v[i], fill);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, CountFillConstructor_ZeroNoAllocation)
{
    const TypeParam fill = makeValue<TypeParam>(1);
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v(0u, fill);
        EXPECT_EQ(checo::getTotalAllocated(), before);
        EXPECT_EQ(v.size(), 0u);
        EXPECT_EQ(v.capacity(), 0u);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

// ===========================================================================
// Initializer-list constructor
// ===========================================================================

TYPED_TEST(VectorTest, InitListConstructor_AllocatesExactly)
{
    const TypeParam a = makeValue<TypeParam>(1);
    const TypeParam b = makeValue<TypeParam>(2);
    const TypeParam c = makeValue<TypeParam>(3);
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v{a, b, c};
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 3);
        EXPECT_EQ(v.size(), 3u);
        EXPECT_EQ(v.capacity(), 3u);
        EXPECT_EQ(v[0], a);
        EXPECT_EQ(v[1], b);
        EXPECT_EQ(v[2], c);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

// ===========================================================================
// Copy constructor
// ===========================================================================

TYPED_TEST(VectorTest, CopyConstructor_AllocatesSameCapacityAsSource)
{
    // Build a source whose size < capacity so we can verify the copy mirrors
    // the full capacity, not just the live elements.
    checo::Vector<TypeParam> src(6u);
    src.push_back(makeValue<TypeParam>(1));
    src.push_back(makeValue<TypeParam>(2));
    // src: size=2, capacity=6

    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> copy(src);
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * src.capacity());
        EXPECT_EQ(copy.size(), src.size());
        EXPECT_EQ(copy.capacity(), src.capacity());
        EXPECT_EQ(copy, src);
        // Verify deep copy: mutating copy must not affect src.
        copy[0] = makeValue<TypeParam>(99);
        EXPECT_EQ(src[0], makeValue<TypeParam>(1));
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, CopyConstructor_EmptySource_NoAllocation)
{
    checo::Vector<TypeParam> src;
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> copy(src);
        EXPECT_EQ(checo::getTotalAllocated(), before);
        EXPECT_EQ(copy.size(), 0u);
        EXPECT_EQ(copy.capacity(), 0u);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

// ===========================================================================
// Move constructor
// ===========================================================================

TYPED_TEST(VectorTest, MoveConstructor_StealStorageNoNewAllocation)
{
    checo::Vector<TypeParam> src;
    src.push_back(makeValue<TypeParam>(10));
    src.push_back(makeValue<TypeParam>(20));
    const size_t srcCap = src.capacity();

    const size_t before = checo::getTotalAllocated();
    checo::Vector<TypeParam> moved(std::move(src));

    EXPECT_EQ(checo::getTotalAllocated(), before); // storage stolen, no new allocation
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_EQ(moved.capacity(), srcCap);
    EXPECT_EQ(moved[0], makeValue<TypeParam>(10));
    EXPECT_EQ(moved[1], makeValue<TypeParam>(20));
    // Source must be left in the null/empty state.
    EXPECT_EQ(src.size(), 0u);
    EXPECT_EQ(src.capacity(), 0u);
    EXPECT_EQ(src.data(), nullptr);
}

// ===========================================================================
// Destructor
// The destructor is exercised implicitly by every scoped vector above;
// these two tests isolate "destructor frees exactly what was allocated".
// ===========================================================================

TYPED_TEST(VectorTest, Destructor_FreesAllAllocatedMemory)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(makeValue<TypeParam>(i));
        EXPECT_GT(checo::getTotalAllocated(), before);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, Destructor_EmptyVector_NoDoubleFree)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

// ===========================================================================
// Copy assignment operator=
// ===========================================================================

TYPED_TEST(VectorTest, CopyAssignment_FreesOldAllocatesForSource)
{
    checo::Vector<TypeParam> src;
    src.push_back(makeValue<TypeParam>(1));
    src.push_back(makeValue<TypeParam>(2));
    src.push_back(makeValue<TypeParam>(3));
    // 3 push_backs from empty → capacity doubles: 0→1→2→4

    checo::Vector<TypeParam> dst;
    dst.push_back(makeValue<TypeParam>(99));
    const size_t dstCapBefore = dst.capacity(); // 1

    const size_t before = checo::getTotalAllocated();
    dst = src;
    // dst's old block (dstCapBefore) freed; new block sized src.capacity() allocated.
    EXPECT_EQ(checo::getTotalAllocated(),
        before - sizeof(TypeParam) * dstCapBefore + sizeof(TypeParam) * src.capacity());
    EXPECT_EQ(dst.size(), src.size());
    EXPECT_EQ(dst.capacity(), src.capacity());
    EXPECT_EQ(dst, src);
    // Deep copy: mutating dst must not affect src.
    dst[0] = makeValue<TypeParam>(77);
    EXPECT_EQ(src[0], makeValue<TypeParam>(1));
}

TYPED_TEST(VectorTest, CopyAssignment_Self_IsNoOp)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(5));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    checo::Vector<TypeParam> *ptr = &v;
    v = *ptr; // self-assign via pointer to suppress compiler warning

    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], makeValue<TypeParam>(5));
}

// ===========================================================================
// Move assignment operator=
// ===========================================================================

TYPED_TEST(VectorTest, MoveAssignment_FreesOldStorageNoNewAllocation)
{
    checo::Vector<TypeParam> src;
    src.push_back(makeValue<TypeParam>(10));
    src.push_back(makeValue<TypeParam>(20));
    const size_t srcCap = src.capacity(); // 2

    checo::Vector<TypeParam> dst;
    dst.push_back(makeValue<TypeParam>(99));
    const size_t dstCap = dst.capacity(); // 1

    const size_t before = checo::getTotalAllocated();
    dst = std::move(src);
    // dst's old block freed (−dstCap); src's block stolen (no new alloc).
    EXPECT_EQ(checo::getTotalAllocated(), before - sizeof(TypeParam) * dstCap);
    EXPECT_EQ(dst.size(), 2u);
    EXPECT_EQ(dst.capacity(), srcCap);
    EXPECT_EQ(dst[0], makeValue<TypeParam>(10));
    EXPECT_EQ(dst[1], makeValue<TypeParam>(20));
    EXPECT_EQ(src.size(), 0u);
    EXPECT_EQ(src.capacity(), 0u);
    EXPECT_EQ(src.data(), nullptr);
}

TYPED_TEST(VectorTest, MoveAssignment_Self_IsNoOp)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(5));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    checo::Vector<TypeParam> *ptr = &v;
    v = std::move(*ptr);

    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(v.size(), 1u);
}

// ===========================================================================
// operator[]
// ===========================================================================

TYPED_TEST(VectorTest, SubscriptOperator_ReadWrite)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    v.push_back(makeValue<TypeParam>(3));

    EXPECT_EQ(v[0], makeValue<TypeParam>(1));
    EXPECT_EQ(v[1], makeValue<TypeParam>(2));
    EXPECT_EQ(v[2], makeValue<TypeParam>(3));

    v[1] = makeValue<TypeParam>(42);
    EXPECT_EQ(v[1], makeValue<TypeParam>(42));
}

TYPED_TEST(VectorTest, SubscriptOperator_Const)
{
    checo::Vector<TypeParam> tmp;
    tmp.push_back(makeValue<TypeParam>(7));
    tmp.push_back(makeValue<TypeParam>(8));

    const checo::Vector<TypeParam> &cv = tmp;
    EXPECT_EQ(cv[0], makeValue<TypeParam>(7));
    EXPECT_EQ(cv[1], makeValue<TypeParam>(8));
}

// ===========================================================================
// operator==
// ===========================================================================

TYPED_TEST(VectorTest, EqualityOperator_EqualVectors)
{
    checo::Vector<TypeParam> a{makeValue<TypeParam>(1), makeValue<TypeParam>(2)};
    checo::Vector<TypeParam> b{makeValue<TypeParam>(1), makeValue<TypeParam>(2)};
    EXPECT_TRUE(a == b);
}

TYPED_TEST(VectorTest, EqualityOperator_DifferentContent)
{
    checo::Vector<TypeParam> a{makeValue<TypeParam>(1), makeValue<TypeParam>(2)};
    checo::Vector<TypeParam> b{makeValue<TypeParam>(1), makeValue<TypeParam>(3)};
    EXPECT_FALSE(a == b);
}

TYPED_TEST(VectorTest, EqualityOperator_DifferentSize)
{
    checo::Vector<TypeParam> a{makeValue<TypeParam>(1), makeValue<TypeParam>(2)};
    checo::Vector<TypeParam> b{makeValue<TypeParam>(1)};
    EXPECT_FALSE(a == b);
}

TYPED_TEST(VectorTest, EqualityOperator_BothEmpty)
{
    const checo::Vector<TypeParam> a;
    const checo::Vector<TypeParam> b;
    EXPECT_TRUE(a == b);
}

TYPED_TEST(VectorTest, EqualityOperator_SameContentDifferentCapacity)
{
    // Equality must depend only on size and elements, not on capacity.
    checo::Vector<TypeParam> a(10u);
    a.push_back(makeValue<TypeParam>(1));
    checo::Vector<TypeParam> b;
    b.push_back(makeValue<TypeParam>(1));
    EXPECT_TRUE(a == b);
}

// ===========================================================================
// data()
// ===========================================================================

TYPED_TEST(VectorTest, Data_NonConst_PointsToFirstElement)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(5));
    TypeParam *ptr = v.data();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, makeValue<TypeParam>(5));
    *ptr = makeValue<TypeParam>(99);
    EXPECT_EQ(v[0], makeValue<TypeParam>(99));
}

TYPED_TEST(VectorTest, Data_Const_PointsToFirstElement)
{
    checo::Vector<TypeParam> tmp;
    tmp.push_back(makeValue<TypeParam>(5));
    const checo::Vector<TypeParam> &cv = tmp;
    const TypeParam *ptr = cv.data();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, makeValue<TypeParam>(5));
}

TYPED_TEST(VectorTest, Data_EmptyVector_ReturnsNull)
{
    const checo::Vector<TypeParam> v;
    EXPECT_EQ(v.data(), nullptr);
}

// ===========================================================================
// begin() / end()
// ===========================================================================

TYPED_TEST(VectorTest, Begin_End_NonConst_PointerArithmeticAndMutation)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    v.push_back(makeValue<TypeParam>(3));

    ASSERT_NE(v.begin(), nullptr);
    EXPECT_EQ(v.end() - v.begin(), static_cast<ptrdiff_t>(v.size()));
    EXPECT_EQ(*v.begin(), makeValue<TypeParam>(1));
    EXPECT_EQ(*(v.end() - 1), makeValue<TypeParam>(3));

    *v.begin() = makeValue<TypeParam>(99);
    EXPECT_EQ(v[0], makeValue<TypeParam>(99));
}

TYPED_TEST(VectorTest, Begin_End_Const)
{
    checo::Vector<TypeParam> tmp;
    tmp.push_back(makeValue<TypeParam>(1));
    tmp.push_back(makeValue<TypeParam>(2));
    const checo::Vector<TypeParam> &cv = tmp;

    ASSERT_NE(cv.begin(), nullptr);
    EXPECT_EQ(cv.end() - cv.begin(), static_cast<ptrdiff_t>(cv.size()));
    EXPECT_EQ(*cv.begin(), makeValue<TypeParam>(1));
    EXPECT_EQ(*(cv.end() - 1), makeValue<TypeParam>(2));
}

TYPED_TEST(VectorTest, Begin_End_EmptyVector_ReturnNull)
{
    const checo::Vector<TypeParam> v;
    EXPECT_EQ(v.begin(), nullptr);
    EXPECT_EQ(v.end(), nullptr);
}

TYPED_TEST(VectorTest, Begin_End_RangeBasedForLoop)
{
    checo::Vector<TypeParam> v{makeValue<TypeParam>(0), makeValue<TypeParam>(1), makeValue<TypeParam>(2)};

    size_t idx = 0;
    for (const TypeParam &elem : v)
        EXPECT_EQ(elem, v[idx++]);
    EXPECT_EQ(idx, 3u);
}

// ===========================================================================
// front() / back()
// ===========================================================================

TYPED_TEST(VectorTest, Front_NonConst_ReadAndWrite)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    EXPECT_EQ(v.front(), makeValue<TypeParam>(1));
    v.front() = makeValue<TypeParam>(99);
    EXPECT_EQ(v[0], makeValue<TypeParam>(99));
}

TYPED_TEST(VectorTest, Front_Const)
{
    checo::Vector<TypeParam> tmp;
    tmp.push_back(makeValue<TypeParam>(42));
    const checo::Vector<TypeParam> &cv = tmp;
    EXPECT_EQ(cv.front(), makeValue<TypeParam>(42));
}

TYPED_TEST(VectorTest, Back_NonConst_ReadAndWrite)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    EXPECT_EQ(v.back(), makeValue<TypeParam>(2));
    v.back() = makeValue<TypeParam>(99);
    EXPECT_EQ(v[1], makeValue<TypeParam>(99));
}

TYPED_TEST(VectorTest, Back_Const)
{
    checo::Vector<TypeParam> tmp;
    tmp.push_back(makeValue<TypeParam>(1));
    tmp.push_back(makeValue<TypeParam>(2));
    const checo::Vector<TypeParam> &cv = tmp;
    EXPECT_EQ(cv.back(), makeValue<TypeParam>(2));
}

// ===========================================================================
// empty() / size() / capacity()
// ===========================================================================

TYPED_TEST(VectorTest, EmptySizeCapacity_DefaultConstructed)
{
    const checo::Vector<TypeParam> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
}

TYPED_TEST(VectorTest, EmptySizeCapacity_AfterPushBacks)
{
    checo::Vector<TypeParam> v;
    EXPECT_TRUE(v.empty());

    v.push_back(makeValue<TypeParam>(1));
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), 1u);
    EXPECT_GE(v.capacity(), 1u);

    v.push_back(makeValue<TypeParam>(2));
    EXPECT_EQ(v.size(), 2u);
    EXPECT_GE(v.capacity(), 2u);
}

// ===========================================================================
// push_back(const T&)  — copy overload
// ===========================================================================

TYPED_TEST(VectorTest, PushBack_Copy_GrowthDoublesCapacity)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;

        const TypeParam v1 = makeValue<TypeParam>(1);
        v.push_back(v1); // 0 → 1
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 1);
        EXPECT_EQ(v.size(), 1u);
        EXPECT_EQ(v.capacity(), 1u);

        const TypeParam v2 = makeValue<TypeParam>(2);
        v.push_back(v2); // 1 → 2
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 2);
        EXPECT_EQ(v.size(), 2u);
        EXPECT_EQ(v.capacity(), 2u);

        const TypeParam v3 = makeValue<TypeParam>(3);
        v.push_back(v3); // 2 → 4
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 4);
        EXPECT_EQ(v.size(), 3u);
        EXPECT_EQ(v.capacity(), 4u);

        EXPECT_EQ(v[0], makeValue<TypeParam>(1));
        EXPECT_EQ(v[1], makeValue<TypeParam>(2));
        EXPECT_EQ(v[2], makeValue<TypeParam>(3));
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, PushBack_Copy_SourceValueIsUnchanged)
{
    checo::Vector<TypeParam> v;
    const TypeParam original = makeValue<TypeParam>(5);
    v.push_back(original);
    EXPECT_EQ(original, makeValue<TypeParam>(5));
}

TYPED_TEST(VectorTest, PushBack_Copy_NoReallocWithinCapacity)
{
    constexpr size_t cap = 4;
    checo::Vector<TypeParam> v(cap);
    const size_t allocAfterReserve = checo::getTotalAllocated();

    for (int i = 0; i < static_cast<int>(cap); ++i) {
        const TypeParam val = makeValue<TypeParam>(i);
        v.push_back(val);
    }
    EXPECT_EQ(checo::getTotalAllocated(), allocAfterReserve);
    EXPECT_EQ(v.size(), cap);
    EXPECT_EQ(v.capacity(), cap);
}

// ===========================================================================
// push_back(T&&)  — move overload
// ===========================================================================

TYPED_TEST(VectorTest, PushBack_Move_GrowthDoublesCapacity)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
        v.push_back(makeValue<TypeParam>(1)); // 0 → 1
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 1);
        v.push_back(makeValue<TypeParam>(2)); // 1 → 2
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 2);
        v.push_back(makeValue<TypeParam>(3)); // 2 → 4
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 4);

        EXPECT_EQ(v.size(), 3u);
        EXPECT_EQ(v.capacity(), 4u);
        EXPECT_EQ(v[0], makeValue<TypeParam>(1));
        EXPECT_EQ(v[1], makeValue<TypeParam>(2));
        EXPECT_EQ(v[2], makeValue<TypeParam>(3));
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, PushBack_Move_NoReallocWithinCapacity)
{
    constexpr size_t cap = 4;
    checo::Vector<TypeParam> v(cap);
    const size_t allocAfterReserve = checo::getTotalAllocated();

    for (int i = 0; i < static_cast<int>(cap); ++i)
        v.push_back(makeValue<TypeParam>(i));

    EXPECT_EQ(checo::getTotalAllocated(), allocAfterReserve);
    EXPECT_EQ(v.size(), cap);
    EXPECT_EQ(v.capacity(), cap);
}

// ===========================================================================
// pop_back()
// ===========================================================================

TYPED_TEST(VectorTest, PopBack_DecreasesSize_CapacityAndStorageUnchanged)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    v.push_back(makeValue<TypeParam>(3));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    v.pop_back();
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
    EXPECT_EQ(v[0], makeValue<TypeParam>(1));
    EXPECT_EQ(v[1], makeValue<TypeParam>(2));
}

TYPED_TEST(VectorTest, PopBack_AllElements_BecomesEmpty)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    v.pop_back();
    v.pop_back();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
}

TYPED_TEST(VectorTest, PopBack_EmptyVector_IsNoOp)
{
    checo::Vector<TypeParam> v;
    const size_t allocBefore = checo::getTotalAllocated();
    v.pop_back();
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
}

// ===========================================================================
// reserve()
// ===========================================================================

TYPED_TEST(VectorTest, Reserve_AllocatesExactAmount)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
        v.reserve(10);
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 10);
        EXPECT_EQ(v.capacity(), 10u);
        EXPECT_EQ(v.size(), 0u);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, Reserve_PreservesExistingElements)
{
    // After two push_backs the capacity is 2; reserve(20) frees that block
    // and allocates a new one for 20 elements.
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
        v.push_back(makeValue<TypeParam>(1));
        v.push_back(makeValue<TypeParam>(2));

        v.reserve(20);
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 20);
        EXPECT_EQ(v.capacity(), 20u);
        EXPECT_EQ(v.size(), 2u);
        EXPECT_EQ(v[0], makeValue<TypeParam>(1));
        EXPECT_EQ(v[1], makeValue<TypeParam>(2));
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, Reserve_SmallerOrEqualCapacity_IsNoOp)
{
    checo::Vector<TypeParam> v;
    v.reserve(10);
    const size_t allocAfter = checo::getTotalAllocated();

    v.reserve(5);
    EXPECT_EQ(checo::getTotalAllocated(), allocAfter);
    EXPECT_EQ(v.capacity(), 10u);

    v.reserve(10);
    EXPECT_EQ(checo::getTotalAllocated(), allocAfter);
    EXPECT_EQ(v.capacity(), 10u);
}

TYPED_TEST(VectorTest, Reserve_PreventsReallocOnSubsequentPushBacks)
{
    checo::Vector<TypeParam> v;
    v.reserve(4);
    const size_t allocAfterReserve = checo::getTotalAllocated();

    for (int i = 0; i < 4; ++i)
        v.push_back(makeValue<TypeParam>(i));

    EXPECT_EQ(checo::getTotalAllocated(), allocAfterReserve);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v.capacity(), 4u);
}

// ===========================================================================
// resize()
// ===========================================================================

TYPED_TEST(VectorTest, Resize_GrowFromEmpty_AllocatesExactly)
{
    const TypeParam fill = makeValue<TypeParam>(7);
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
        v.resize(5, fill);
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * 5);
        EXPECT_EQ(v.size(), 5u);
        EXPECT_EQ(v.capacity(), 5u);
        for (size_t i = 0; i < 5; ++i)
            EXPECT_EQ(v[i], fill);
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, Resize_WithinReservedCapacity_NoReallocation)
{
    checo::Vector<TypeParam> v;
    v.reserve(10);
    const size_t allocAfterReserve = checo::getTotalAllocated();

    v.resize(6, makeValue<TypeParam>(3));
    EXPECT_EQ(checo::getTotalAllocated(), allocAfterReserve); // fits; no new block
    EXPECT_EQ(v.size(), 6u);
    EXPECT_EQ(v.capacity(), 10u);
    for (size_t i = 0; i < 6; ++i)
        EXPECT_EQ(v[i], makeValue<TypeParam>(3));
}

TYPED_TEST(VectorTest, Resize_Shrink_NoReallocation)
{
    checo::Vector<TypeParam> v;
    for (int i = 0; i < 5; ++i)
        v.push_back(makeValue<TypeParam>(i));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    v.resize(2);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
    EXPECT_EQ(v[0], makeValue<TypeParam>(0));
    EXPECT_EQ(v[1], makeValue<TypeParam>(1));
}

TYPED_TEST(VectorTest, Resize_SameSize_IsNoOp)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    v.resize(2);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
}

TYPED_TEST(VectorTest, Resize_ToZero_BecomesEmpty)
{
    checo::Vector<TypeParam> v;
    for (int i = 0; i < 3; ++i)
        v.push_back(makeValue<TypeParam>(i));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    v.resize(0);
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
}

// ===========================================================================
// shrink_to_fit()
// ===========================================================================

TYPED_TEST(VectorTest, ShrinkToFit_ReleasesExcessCapacity)
{
    const size_t before = checo::getTotalAllocated();
    {
        checo::Vector<TypeParam> v;
        v.push_back(makeValue<TypeParam>(1));
        v.push_back(makeValue<TypeParam>(2));
        v.reserve(20);
        EXPECT_EQ(v.capacity(), 20u);
        EXPECT_EQ(v.size(), 2u);

        v.shrink_to_fit();
        EXPECT_EQ(v.capacity(), v.size()); // trimmed to exact fit
        EXPECT_EQ(checo::getTotalAllocated() - before, sizeof(TypeParam) * v.size());
        EXPECT_EQ(v[0], makeValue<TypeParam>(1));
        EXPECT_EQ(v[1], makeValue<TypeParam>(2));
    }
    EXPECT_EQ(checo::getTotalAllocated(), before);
}

TYPED_TEST(VectorTest, ShrinkToFit_AlreadyExact_IsNoOp)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    v.push_back(makeValue<TypeParam>(3));
    // After 3 push_backs: capacity=4, size=3. Trim once.
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());

    const size_t allocBefore = checo::getTotalAllocated();
    v.shrink_to_fit(); // already capacity==size — must be a no-op
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
    EXPECT_EQ(v.capacity(), v.size());
}

// ===========================================================================
// clear()
// ===========================================================================

TYPED_TEST(VectorTest, Clear_ResetsSize_RetainsCapacityAndStorage)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    v.push_back(makeValue<TypeParam>(3));
    const size_t capBefore = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();
    const TypeParam *ptrBefore = v.data();

    v.clear();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), capBefore);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
    EXPECT_EQ(v.data(), ptrBefore); // same storage block retained
}

TYPED_TEST(VectorTest, Clear_AllowsReuseOfStorage_NoRealloc)
{
    checo::Vector<TypeParam> v;
    v.push_back(makeValue<TypeParam>(1));
    v.push_back(makeValue<TypeParam>(2));
    const size_t cap = v.capacity();
    const size_t allocBefore = checo::getTotalAllocated();

    v.clear();
    for (size_t i = 0; i < cap; ++i)
        v.push_back(makeValue<TypeParam>(static_cast<int>(i)));

    EXPECT_EQ(checo::getTotalAllocated(), allocBefore); // storage reused
    EXPECT_EQ(v.size(), cap);
}

TYPED_TEST(VectorTest, Clear_EmptyVector_IsNoOp)
{
    checo::Vector<TypeParam> v;
    const size_t allocBefore = checo::getTotalAllocated();
    v.clear();
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_EQ(checo::getTotalAllocated(), allocBefore);
}

} // namespace checo::testing