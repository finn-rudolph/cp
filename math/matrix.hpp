#include <bits/stdc++.h>
using namespace std;

template <typename T>
using Matrix = vector<vector<T>>;

template <typename T>
Matrix<T> make_identity(size_t n)
{
    Matrix<T> a(n, vector<T>(n));
    for (size_t i = 0; i < n; i++)
        a[i][i] = 1;
    return a;
}

template <typename T>
Matrix<T> matrix_multiply(Matrix<T> const &a, Matrix<T> const &b)
{
    assert(a[0].size() == b.size());
    Matrix<T> c(a.size(), vector<T>(b[0].size()));

    for (size_t i = 0; i < c.size(); i++)
        for (size_t j = 0; j < c[i].size(); j++)
            for (size_t k = 0; k < b.size(); k++)
                c[i][j] += a[i][k] * b[k][j];

    return c;
}

template <typename T>
Matrix<T> matrix_exp(Matrix<T> a, size_t y)
{
    Matrix<T> c = make_identity<T>(a.size());
    for (size_t i = 0; i < c.size(); i++)
        c[i][i] = 1;

    while (y)
    {
        if (y & 1)
            c = matrix_multiply(c, a);
        a = matrix_multiply(a, a);
        y >>= 1;
    }

    return c;
}

template <typename T>
vector<T> matrix_vector_multiply(Matrix<T> const &a, vector<T> const &x)
{
    assert(x.size() == a[0].size());
    vector<T> y(a.size());

    for (size_t i = 0; i < y.size(); i++)
        for (size_t j = 0; j < x.size(); j++)
            y[i] += a[i][j] * x[j];

    return y;
}
