#include <array>
#include <initializer_list>

namespace checo::math
{

template <typename TData, size_t Rows, size_t Cols> class Matrix
{
  public:
    Matrix(const Matrix<TData, Rows, Cols> &) = default;
    Matrix(Matrix<TData, Rows, Cols> &&) = default;
    virtual ~Matrix() = default;

    Matrix()
    {
        for (auto &row : mData)
        {
            row.fill(TData());
        }
    }

    Matrix(const std::initializer_list<std::initializer_list<TData>> &data)
    {
        size_t row = 0;
        for (const auto &rowData : data)
        {
            size_t col = 0;
            for (const auto &element : rowData)
            {
                mData[row][col] = element;
                ++col;
            }
            ++row;
        }
    }

  public:
    Matrix<TData, Rows, Cols> &operator=(const Matrix<TData, Rows, Cols> &) = default;
    Matrix<TData, Rows, Cols> &operator=(Matrix<TData, Rows, Cols> &&) = default;

  public:
    inline TData &operator()(const size_t row, const size_t col)
    {
        return mData[row][col];
    }

    inline const TData &operator()(const size_t row, const size_t col) const
    {
        return mData[row][col];
    }

    bool operator==(const Matrix<TData, Rows, Cols> &other) const
    {
        return mData == other.mData;
    }

    template <size_t OtherRows, size_t OtherCols>
    Matrix<TData, Rows, OtherCols> operator*(const Matrix<TData, OtherRows, OtherCols> &other) const
    {
        Matrix<TData, Rows, OtherCols> result;
        for (size_t i = 0; i < Rows; ++i)
        {
            for (size_t j = 0; j < OtherCols; ++j)
            {
                result(i, j) = 0;
                for (size_t k = 0; k < Cols; ++k)
                {
                    result(i, j) += mData[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

  private:
    std::array<std::array<TData, Cols>, Rows> mData;
};

} // namespace checo::math
