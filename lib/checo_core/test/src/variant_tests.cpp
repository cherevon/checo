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

#include "checo/byte_array.h"
#include "checo/variant.h"

#include <gtest/gtest.h>

#include <cstring>
#include <limits>

namespace checo::testing
{

struct VariantTestCase
{
    std::string m_TestName{};
    Variant::Type m_ExpectedType{};
    std::function<Variant()> m_CreateVariant{};
    std::function<void(const Variant &)> m_CheckGetters{};
    std::function<void(const Variant &)> m_CheckOperators{};
};

class VariantTest : public ::testing::TestWithParam<VariantTestCase>
{
};

TEST(VariantTest, DefaultConstructorIsEmpty)
{
    Variant v{};
    ASSERT_EQ(v.getType(), Variant::Type::Empty);
}

TEST_P(VariantTest, CheckDataTypes)
{
    const auto &p = GetParam();

    Variant v = p.m_CreateVariant();

    EXPECT_EQ(v.getType(), p.m_ExpectedType);
    p.m_CheckGetters(v);
    p.m_CheckOperators(v);
}

INSTANTIATE_TEST_SUITE_P(DataTypes, VariantTest,
    ::testing::Values(

        VariantTestCase{
            .m_TestName = "Bool_False",
            .m_ExpectedType = Variant::Type::Bool,
            .m_CreateVariant = []() { return Variant(false); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isBool());
                    ASSERT_FALSE(v.getBool());
                },
            .m_CheckOperators =
                [](const Variant &v) {
                    ASSERT_FALSE(v == true);
                    ASSERT_TRUE(v == false);
                },
        },
        VariantTestCase{
            .m_TestName = "Bool_True",
            .m_ExpectedType = Variant::Type::Bool,
            .m_CreateVariant = []() { return Variant(true); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isBool());
                    ASSERT_TRUE(v.getBool());
                },
            .m_CheckOperators =
                [](const Variant &v) {
                    ASSERT_TRUE(v == true);
                    ASSERT_FALSE(v == false);
                },
        },
        VariantTestCase{
            .m_TestName = "Int32_Min",
            .m_ExpectedType = Variant::Type::Int32,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<int32_t>::min()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isInt32());
                    ASSERT_EQ(v.getInt32(), std::numeric_limits<int32_t>::min());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<int32_t>::min()); },
        },
        VariantTestCase{
            .m_TestName = "Int32_Zero",
            .m_ExpectedType = Variant::Type::Int32,
            .m_CreateVariant = []() { return Variant(static_cast<int32_t>(0)); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isInt32());
                    ASSERT_EQ(v.getInt32(), 0);
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == 0); },
        },
        VariantTestCase{
            .m_TestName = "Int32_Max",
            .m_ExpectedType = Variant::Type::Int32,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<int32_t>::max()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isInt32());
                    EXPECT_EQ(v.getInt32(), std::numeric_limits<int32_t>::max());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<int32_t>::max()); },
        },
        VariantTestCase{
            .m_TestName = "Int64_Min",
            .m_ExpectedType = Variant::Type::Int64,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<int64_t>::min()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isInt64());
                    ASSERT_EQ(v.getInt64(), std::numeric_limits<int64_t>::min());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<int64_t>::min()); },
        },
        VariantTestCase{
            .m_TestName = "Int64_Zero",
            .m_ExpectedType = Variant::Type::Int64,
            .m_CreateVariant = []() { return Variant(static_cast<int64_t>(0)); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isInt64());
                    ASSERT_EQ(v.getInt64(), 0);
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == static_cast<int64_t>(0)); },
        },
        VariantTestCase{
            .m_TestName = "Int64_Max",
            .m_ExpectedType = Variant::Type::Int64,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<int64_t>::max()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isInt64());
                    ASSERT_EQ(v.getInt64(), std::numeric_limits<int64_t>::max());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<int64_t>::max()); },
        },
        VariantTestCase{
            .m_TestName = "UnsignedInt32_Min",
            .m_ExpectedType = Variant::Type::UnsignedInt32,
            .m_CreateVariant = []() { return Variant(static_cast<uint32_t>(0)); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isUnsignedInt32());
                    ASSERT_EQ(v.getUnsignedInt32(), 0);
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == static_cast<uint32_t>(0)); },
        },
        VariantTestCase{
            .m_TestName = "UnsignedInt32_Max",
            .m_ExpectedType = Variant::Type::UnsignedInt32,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<uint32_t>::max()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isUnsignedInt32());
                    ASSERT_EQ(v.getUnsignedInt32(), std::numeric_limits<uint32_t>::max());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<uint32_t>::max()); },
        },
        VariantTestCase{
            .m_TestName = "UnsignedInt64_Min",
            .m_ExpectedType = Variant::Type::UnsignedInt64,
            .m_CreateVariant = []() { return Variant(static_cast<uint64_t>(0)); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isUnsignedInt64());
                    ASSERT_EQ(v.getUnsignedInt64(), 0);
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == static_cast<uint64_t>(0)); },
        },
        VariantTestCase{
            .m_TestName = "UnsignedInt64_Max",
            .m_ExpectedType = Variant::Type::UnsignedInt64,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<uint64_t>::max()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isUnsignedInt64());
                    ASSERT_EQ(v.getUnsignedInt64(), std::numeric_limits<uint64_t>::max());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<uint64_t>::max()); },
        },
        VariantTestCase{
            .m_TestName = "Float_Min",
            .m_ExpectedType = Variant::Type::Float,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<float>::min()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isFloat());
                    ASSERT_EQ(v.getFloat(), std::numeric_limits<float>::min());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<float>::min()); },
        },
        VariantTestCase{
            .m_TestName = "Float_Zero",
            .m_ExpectedType = Variant::Type::Float,
            .m_CreateVariant = []() { return Variant(0.0f); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isFloat());
                    ASSERT_EQ(v.getFloat(), 0.0f);
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == 0.0f); },
        },
        VariantTestCase{
            .m_TestName = "Float_Max",
            .m_ExpectedType = Variant::Type::Float,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<float>::max()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isFloat());
                    ASSERT_EQ(v.getFloat(), std::numeric_limits<float>::max());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<float>::max()); },
        },
        VariantTestCase{
            .m_TestName = "Float_Infinity",
            .m_ExpectedType = Variant::Type::Float,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<float>::infinity()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isFloat());
                    ASSERT_EQ(v.getFloat(), std::numeric_limits<float>::infinity());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<float>::infinity()); },
        },
        VariantTestCase{
            .m_TestName = "Float_Quiet_NaN",
            .m_ExpectedType = Variant::Type::Float,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<float>::quiet_NaN()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isFloat());
                    ASSERT_TRUE(std::isnan(v.getFloat()));
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v != v); },
        },
        VariantTestCase{
            .m_TestName = "Float_Signaling_NaN",
            .m_ExpectedType = Variant::Type::Float,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<float>::signaling_NaN()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isFloat());
                    ASSERT_TRUE(std::isnan(v.getFloat()));
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v != v); },
        },
        VariantTestCase{
            .m_TestName = "Double_Min",
            .m_ExpectedType = Variant::Type::Double,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<double>::min()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isDouble());
                    ASSERT_EQ(v.getDouble(), std::numeric_limits<double>::min());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<double>::min()); },
        },
        VariantTestCase{
            .m_TestName = "Double_Zero",
            .m_ExpectedType = Variant::Type::Double,
            .m_CreateVariant = []() { return Variant(0.0); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isDouble());
                    ASSERT_EQ(v.getDouble(), 0.0);
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == 0.0); },
        },
        VariantTestCase{
            .m_TestName = "Double_Max",
            .m_ExpectedType = Variant::Type::Double,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<double>::max()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isDouble());
                    ASSERT_EQ(v.getDouble(), std::numeric_limits<double>::max());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<double>::max()); },
        },
        VariantTestCase{
            .m_TestName = "Double_Infinity",
            .m_ExpectedType = Variant::Type::Double,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<double>::infinity()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isDouble());
                    ASSERT_EQ(v.getDouble(), std::numeric_limits<double>::infinity());
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == std::numeric_limits<double>::infinity()); },
        },
        VariantTestCase{
            .m_TestName = "Double_Quiet_NaN",
            .m_ExpectedType = Variant::Type::Double,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<double>::quiet_NaN()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isDouble());
                    ASSERT_TRUE(std::isnan(v.getDouble()));
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v != v); },
        },
        VariantTestCase{
            .m_TestName = "Double_Signaling_NaN",
            .m_ExpectedType = Variant::Type::Double,
            .m_CreateVariant = []() { return Variant(std::numeric_limits<double>::signaling_NaN()); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isDouble());
                    ASSERT_TRUE(std::isnan(v.getDouble()));
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v != v); },
        },
        VariantTestCase{
            .m_TestName = "ByteArray",
            .m_ExpectedType = Variant::Type::ByteArray,
            .m_CreateVariant = []() { return Variant(ByteArray("test", 4)); },
            .m_CheckGetters =
                [](const Variant &v) {
                    ASSERT_TRUE(v.isByteArray());
                    ASSERT_EQ(v.getByteArray(), ByteArray("test", 4));
                },
            .m_CheckOperators = [](const Variant &v) { ASSERT_TRUE(v == ByteArray("test", 4)); },
        }

        ),
    [](const ::testing::TestParamInfo<VariantTestCase> &info) { return info.param.m_TestName; });

} // namespace checo::testing