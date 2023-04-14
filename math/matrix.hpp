#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N, size_t M>
struct Matrix
{
    T x[N][M];

    T *operator[](size_t i) { return x[i]; }

    template <size_t L>
    Matrix<T, N, L> operator*(Matrix<T, M, L> mat)
    {
        Matrix<T, N, L> z;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < L; ++j)
                for (size_t k = z[i][j] = 0; k < M; ++k)
                    z[i][j] = z[i][j] + x[i][k] * mat[k][j];
        return z;
    }

    Matrix<T, N, M> operator+(Matrix<T, N, M> mat)
    {
        Matrix<T, N, M> z;
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                z[i][j] = x[i][j] + mat[i][j];
        return z;
    }

    array<T, N> operator*(array<T, M> vec)
    {
        array<T, N> z;
        for (size_t i = 0; i < N; i++)
            for (size_t j = z[i] = 0; j < M; j++)
                z[i] = z[i] + x[i][j] * vec[j];
        return z;
    }
};

template <typename T, size_t N>
Matrix<T, N, N> make_identity()
{
    Matrix<T, N, N> z;
    memset(z.x, 0, sizeof z.x);
    for (size_t i = 0; i < N; i++)
        z[i][i] = 1;
    return z;
}