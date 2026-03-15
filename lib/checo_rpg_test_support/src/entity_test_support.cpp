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

#include "checo/rpg/entity_test_support.h"
#include "test_support.h"

namespace checo::rpg
{

static constexpr const char *ENTITY_TYPE = "Entity";

bool deepEqual(const Entity &left, const Entity &right)
{
    return left.m_Id == right.m_Id && left.m_Category == right.m_Category && left.m_Name == right.m_Name &&
           left.m_Description == right.m_Description;
}

std::shared_ptr<Entity> createTestEntity()
{
    auto result = std::make_shared<Entity>();
    result->m_Id = getNextTestEntityId();
    result->m_Category = createTestCategory(ENTITY_TYPE, result->m_Id);
    result->m_Name = createTestName(ENTITY_TYPE, result->m_Id);
    result->m_Description = createTestDescription(ENTITY_TYPE, result->m_Id);
    return result;
}

} // namespace checo::rpg