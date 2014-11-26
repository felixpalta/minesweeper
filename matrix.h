#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>
#include <string>

template<class T>
class Matrix
{
public:
    Matrix(int r, int c);

    int rows() const { return _rows; }
    int cols() const { return _cols; }

    T& operator() (int row, int col);
    const T& operator() (int row, int col) const;

    struct Bad_subscript : std::out_of_range
    {
        int i;
        int j;
        Bad_subscript(int ii, int jj)
            : std::out_of_range("Invalid matrix subscripts: " + std::to_string(i) + ", " + std::to_string(j)),
            i(ii),
            j(jj)
            { }
    };

private:
    int _rows;
    int _cols;
    std::vector<T> data;

    Matrix(const Matrix& m) = delete;
    Matrix& operator=(Matrix const& m) = delete;

};

template<class T>
Matrix<T>::Matrix(int r, int c)
    :_rows(0), _cols(0), data()
{
    if (r <= 0 || c <= 0)
        throw Bad_subscript(r, c);

    _rows = r;
    _cols = c;

    data = std::vector<T>(unsigned(r * c));
}

template<class T>
T& Matrix<T>::operator() (int row, int col)
{
    if (row >= _rows || col >= _cols || row < 0 || col < 0)
        throw Bad_subscript(row, col);

    return data.at(unsigned(_cols * row + col));
}

template<class T>
const T& Matrix<T>::operator() (int row, int col) const
{
    if (row >= _rows || col >= _cols || row < 0 || col < 0)
        throw Bad_subscript(row, col);

    return data.at(unsigned(_cols * row + col));
}


#endif // MATRIX_H
