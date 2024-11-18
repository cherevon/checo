/**
    @file
    @brief This file contains tests to check multiplication of checo::math::Matrix objects.
*/

#include "checo/math/matrix.h"

#include <gtest/gtest.h>

namespace checo::math::test
{

TEST(MatrixMultiplyFixture, Multiply)
{
    Matrix<int, 2, 3> matrix1 = {
        {1, 2, 3},
        {3, 4, 5},
    };
    Matrix<int, 3, 2> matrix2{
        {5, 6},
        {7, 8},
        {9, 10},
    };

    Matrix<int, 2, 2> result = matrix1 * matrix2;
    Matrix<int, 2, 2> expectedResult{
        {46, 52},
        {88, 100},
    };

    ASSERT_EQ(result, expectedResult);
}

} // namespace checo::math::test
