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
#include "checo/string.h"
#include "checo/vector.h"

#include <gtest/gtest.h>

#include <string>

namespace checo::testing
{

template <typename T>
class VectorTest : public ::testing::Test
{
};

using TestTypes = ::testing::Types<int, double, checo::String, std::string>;
TYPED_TEST_SUITE(VectorTest, TestTypes);

template <typename T>
T getNextValue();

template <>
int getNextValue<int>()
{
    static int value = 777;
    return value++;
}

template <>
double getNextValue<double>()
{
    static double value = 33.33;
    return value += 1.1;
}

template <>
std::string getNextValue<std::string>()
{
    static int counter = 0;
    return "str" + std::to_string(counter++);
}

template <>
checo::String getNextValue<checo::String>()
{
    static int counter = 0;
    return std::string("str" + std::to_string(counter++)).c_str();
}

TYPED_TEST(VectorTest, DefaultConstructor)
{
    checo::Vector<TypeParam> testContainer;
    ASSERT_EQ(0u, testContainer.size());
    ASSERT_TRUE(testContainer.empty());
    ASSERT_EQ(0u, testContainer.capacity());
    ASSERT_EQ(0u, checo::getTotalAllocated());
}

TYPED_TEST(VectorTest, CapacityConstructor)
{
    checo::Vector<TypeParam> testContainer(10);
    ASSERT_EQ(0u, testContainer.size());
    ASSERT_TRUE(testContainer.empty());
    ASSERT_EQ(10u, testContainer.capacity());
    ASSERT_EQ(10u * sizeof(TypeParam), checo::getTotalAllocated());
}

TYPED_TEST(VectorTest, FillConstructor)
{
    static constexpr size_t ITEM_COUNT = 33;
    static const TypeParam VALUE = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer(ITEM_COUNT, VALUE);
    ASSERT_FALSE(testContainer.empty());
    ASSERT_EQ(ITEM_COUNT, testContainer.size());
    for (size_t i = 0; i < testContainer.size(); ++i) {
        ASSERT_EQ(VALUE, testContainer[i]);
    }
    ASSERT_EQ(ITEM_COUNT, testContainer.capacity());
    ASSERT_EQ(ITEM_COUNT * sizeof(TypeParam), checo::getTotalAllocated());
}

TYPED_TEST(VectorTest, InitializerListConstructor)
{
    checo::Vector<TypeParam> testContainer = {getNextValue<TypeParam>(), getNextValue<TypeParam>()};
    ASSERT_FALSE(testContainer.empty());
    ASSERT_EQ(2u, testContainer.size());
    ASSERT_EQ(testContainer.size() * sizeof(TypeParam), checo::getTotalAllocated());
}

TYPED_TEST(VectorTest, CopyConstructor)
{
    checo::Vector<TypeParam> sourceContainer = {getNextValue<TypeParam>(), getNextValue<TypeParam>()};
    ASSERT_FALSE(sourceContainer.empty());
    ASSERT_EQ(2u, sourceContainer.size());
    const size_t allocatedMem = checo::getTotalAllocated();

    checo::Vector<TypeParam> testContainer(sourceContainer);
    ASSERT_EQ(sourceContainer.size(), testContainer.size());
    ASSERT_EQ(allocatedMem * 2, checo::getTotalAllocated());
    ASSERT_EQ(testContainer, sourceContainer);
}

TYPED_TEST(VectorTest, MoveConstructor)
{
    checo::Vector<TypeParam> sourceContainer = {getNextValue<TypeParam>(), getNextValue<TypeParam>()};
    ASSERT_FALSE(sourceContainer.empty());
    ASSERT_EQ(2u, sourceContainer.size());
    const size_t allocatedMem = checo::getTotalAllocated();

    checo::Vector<TypeParam> testContainer(std::move(sourceContainer));
    ASSERT_EQ(2u, testContainer.size());
    ASSERT_EQ(allocatedMem, checo::getTotalAllocated());
    ASSERT_TRUE(sourceContainer.empty());
}

TYPED_TEST(VectorTest, Destructor)
{
    const size_t startAllocMem = checo::getTotalAllocated();

    {
        checo::Vector<TypeParam> testContainer = {getNextValue<TypeParam>(), getNextValue<TypeParam>()};
        ASSERT_NE(startAllocMem, checo::getTotalAllocated());
    }

    ASSERT_EQ(startAllocMem, checo::getTotalAllocated());
}

TYPED_TEST(VectorTest, CopyAssignmentOperator)
{
    checo::Vector<TypeParam> sourceContainer = {getNextValue<TypeParam>(), getNextValue<TypeParam>()};
    ASSERT_FALSE(sourceContainer.empty());
    ASSERT_EQ(2u, sourceContainer.size());
    const size_t allocatedMem = checo::getTotalAllocated();

    checo::Vector<TypeParam> testContainer;
    testContainer = sourceContainer;
    ASSERT_EQ(sourceContainer.size(), testContainer.size());
    ASSERT_EQ(allocatedMem * 2, checo::getTotalAllocated());
    ASSERT_EQ(testContainer, sourceContainer);
}

TYPED_TEST(VectorTest, MoveAssignmentOperator)
{
    checo::Vector<TypeParam> sourceContainer = {getNextValue<TypeParam>(), getNextValue<TypeParam>()};
    ASSERT_FALSE(sourceContainer.empty());
    ASSERT_EQ(2u, sourceContainer.size());
    const size_t allocatedMem = checo::getTotalAllocated();

    checo::Vector<TypeParam> testContainer;
    testContainer = std::move(sourceContainer);
    ASSERT_EQ(2u, testContainer.size());
    ASSERT_EQ(allocatedMem, checo::getTotalAllocated());
    ASSERT_TRUE(sourceContainer.empty());
}

TYPED_TEST(VectorTest, OperatorSquareBrackets)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(testContainer[0], value0);
    ASSERT_EQ(testContainer[1], value1);
}

TYPED_TEST(VectorTest, OperatorEqual)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> container1 = {value0, value1};
    checo::Vector<TypeParam> container2 = {value0, value1};
    checo::Vector<TypeParam> container3 = {value1, value0};

    ASSERT_TRUE(container1 == container2);
    ASSERT_FALSE(container1 == container3);
}

TYPED_TEST(VectorTest, Data)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(testContainer.data()[0], value0);
    ASSERT_EQ(testContainer.data()[1], value1);
}

TYPED_TEST(VectorTest, ConstData)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    const checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(testContainer.data()[0], value0);
    ASSERT_EQ(testContainer.data()[1], value1);
}

TYPED_TEST(VectorTest, Begin)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(*testContainer.begin(), value0);
    ASSERT_EQ(*(testContainer.begin() + 1), value1);
}

TYPED_TEST(VectorTest, ConstBegin)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    const checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(*testContainer.begin(), value0);
    ASSERT_EQ(*(testContainer.begin() + 1), value1);
}

TYPED_TEST(VectorTest, End)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(*(testContainer.end() - 2), value0);
    ASSERT_EQ(*(testContainer.end() - 1), value1);

    testContainer.clear();
    ASSERT_EQ(testContainer.end(), testContainer.begin());
}

TYPED_TEST(VectorTest, ConstEnd)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    const checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(*(testContainer.end() - 2), value0);
    ASSERT_EQ(*(testContainer.end() - 1), value1);
}

TYPED_TEST(VectorTest, Front)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(testContainer.front(), value0);
}

TYPED_TEST(VectorTest, ConstFront)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    const checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(testContainer.front(), value0);
}

TYPED_TEST(VectorTest, Back)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(testContainer.back(), value1);
}

TYPED_TEST(VectorTest, ConstBack)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    const checo::Vector<TypeParam> testContainer = {value0, value1};
    ASSERT_EQ(testContainer.back(), value1);
}

TYPED_TEST(VectorTest, Empty)
{
    checo::Vector<TypeParam> testContainer;
    ASSERT_TRUE(testContainer.empty());

    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();
    testContainer = {value0, value1};
    ASSERT_FALSE(testContainer.empty());
}

TYPED_TEST(VectorTest, Size)
{
    checo::Vector<TypeParam> testContainer;
    ASSERT_EQ(testContainer.size(), 0);

    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();
    testContainer = {value0, value1};
    ASSERT_EQ(testContainer.size(), 2);
}

TYPED_TEST(VectorTest, Capacity)
{
    checo::Vector<TypeParam> testContainer;
    ASSERT_EQ(testContainer.capacity(), 0);

    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();
    testContainer = {value0, value1};
    ASSERT_GE(testContainer.capacity(), 2);
}

TYPED_TEST(VectorTest, PushBack)
{
    checo::Vector<TypeParam> testContainer;
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    testContainer.push_back(value0);
    testContainer.push_back(value1);
    ASSERT_EQ(testContainer.size(), 2);
    ASSERT_EQ(testContainer[0], value0);
    ASSERT_EQ(testContainer[1], value1);
}

TYPED_TEST(VectorTest, PopBack)
{
    checo::Vector<TypeParam> testContainer;
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    testContainer.push_back(value0);
    testContainer.push_back(value1);
    testContainer.pop_back();
    ASSERT_EQ(testContainer.size(), 1);
    ASSERT_EQ(testContainer[0], value0);
}

TYPED_TEST(VectorTest, Reserve)
{
    checo::Vector<TypeParam> testContainer;
    ASSERT_EQ(testContainer.capacity(), 0);

    testContainer.reserve(2);
    ASSERT_EQ(testContainer.capacity(), 2);
    ASSERT_EQ(testContainer.size(), 0);
    ASSERT_TRUE(testContainer.empty());
    ASSERT_EQ(checo::getTotalAllocated(), sizeof(TypeParam) * 2);
}

TYPED_TEST(VectorTest, Resize)
{
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    checo::Vector<TypeParam> testContainer;
    ASSERT_EQ(testContainer.size(), 0);

    testContainer.resize(2, value0);
    ASSERT_EQ(testContainer.size(), 2);
    ASSERT_EQ(testContainer[0], value0);
    ASSERT_EQ(testContainer[1], value0);
    ASSERT_EQ(checo::getTotalAllocated(), sizeof(TypeParam) * 2);

    testContainer.resize(3, value1);
    ASSERT_EQ(testContainer.size(), 3);
    ASSERT_EQ(testContainer[0], value0);
    ASSERT_EQ(testContainer[1], value0);
    ASSERT_EQ(testContainer[2], value1);
    ASSERT_EQ(checo::getTotalAllocated(), sizeof(TypeParam) * 3);
}

TYPED_TEST(VectorTest, ShrinkToFit)
{
    checo::Vector<TypeParam> testContainer;
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    testContainer.push_back(value0);
    testContainer.push_back(value1);
    testContainer.reserve(10);
    ASSERT_GE(testContainer.capacity(), 10);
    ASSERT_EQ(checo::getTotalAllocated(), sizeof(TypeParam) * 10);

    testContainer.shrink_to_fit();
    ASSERT_EQ(testContainer.capacity(), 2);
    ASSERT_EQ(checo::getTotalAllocated(), sizeof(TypeParam) * 2);
}

TYPED_TEST(VectorTest, Clear)
{
    checo::Vector<TypeParam> testContainer;
    const TypeParam value0 = getNextValue<TypeParam>();
    const TypeParam value1 = getNextValue<TypeParam>();

    testContainer.push_back(value0);
    testContainer.push_back(value1);
    ASSERT_EQ(testContainer.size(), 2);

    testContainer.clear();
    ASSERT_TRUE(testContainer.empty());
    ASSERT_EQ(testContainer.size(), 0);
}

} // namespace checo::testing