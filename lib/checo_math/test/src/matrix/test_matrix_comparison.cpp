/**
    @file
    @brief This file contains tests to check comparison of checo::math::Matrix objects.
*/

#include "checo/math/matrix.h"

#include <gtest/gtest.h>

namespace checo::math::test
{

TEST(MatrixComparisonFixture, Equal)
{
    Matrix<int, 2, 2> matrix1{
        {1, 2},
        {3, 4},
    };

    Matrix<int, 2, 2> matrix2{
        {1, 2},
        {3, 4},
    };

    ASSERT_TRUE(matrix1 == matrix2);
}

TEST(MatrixComparisonFixture, NotEqual)
{
    Matrix<int, 2, 2> matrix1{
        {1, 2},
        {3, 4},
    };

    Matrix<int, 2, 2> matrix2{
        {5, 6},
        {7, 8},
    };

    ASSERT_TRUE(matrix1 != matrix2);
}

} // namespace checo::math::test
