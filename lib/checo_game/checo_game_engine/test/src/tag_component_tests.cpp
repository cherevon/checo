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

#include <gtest/gtest.h>

namespace checo::game::testing
{

constexpr const char *TEST_TAG_1 = "first_test_tag";
constexpr const char *TEST_TAG_2 = "second_test_tag";

TEST(TagComponentTests, AddSingleTag)
{
    TagComponent tagComponent;
    tagComponent.addTag(TEST_TAG_1);
    ASSERT_TRUE(tagComponent.hasTag(TEST_TAG_1));
}

TEST(TagComponentTests, AddMultipleTags)
{
    TagComponent tagComponent;
    tagComponent.addTag(TEST_TAG_1);
    tagComponent.addTag(TEST_TAG_2);
    ASSERT_TRUE(tagComponent.hasTag(TEST_TAG_1));
    ASSERT_TRUE(tagComponent.hasTag(TEST_TAG_2));
}

TEST(TagComponentTests, RemoveTag)
{
    TagComponent tagComponent;
    tagComponent.addTag(TEST_TAG_1);
    ASSERT_TRUE(tagComponent.hasTag(TEST_TAG_1));
    tagComponent.removeTag(TEST_TAG_1);
    ASSERT_FALSE(tagComponent.hasTag(TEST_TAG_1));
}

} // namespace checo::game::testing