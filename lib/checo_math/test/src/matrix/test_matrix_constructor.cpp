/**
    @file
    @brief This file contains tests to check constructors of checo::math::Matrix objects.
*/

#include "checo/math/matrix.h"

#include <gtest/gtest.h>

namespace checo::math::test
{

TEST(MatrixConstructorFixture, CreateEmpty)
{
    Matrix<int, 2, 2> testMatrix;

    ASSERT_EQ(testMatrix(0, 0), 0);
    ASSERT_EQ(testMatrix(0, 1), 0);
    ASSERT_EQ(testMatrix(1, 0), 0);
    ASSERT_EQ(testMatrix(1, 1), 0);
}

TEST(MatrixConstructorFixture, CreateFromInitializerList)
{
    Matrix<int, 2, 2> testMatrix{
        {-10, 2},
        {3, 34},
    };

    ASSERT_EQ(testMatrix(0, 0), -10);
    ASSERT_EQ(testMatrix(0, 1), 2);
    ASSERT_EQ(testMatrix(1, 0), 3);
    ASSERT_EQ(testMatrix(1, 1), 34);
}

} // namespace checo::math::test
