#include <bits/stdc++.h>
using namespace std;

/*
Convolution in O(n log n) via FFT.
*/

template <typename T>
constexpr T ceiled_lg(T n) // to keep things portable
{
    T x = 1;
    while ((T)1 << x < n)
        ++x;
    return x;
}

template <size_t N, typename T>
void bit_reverse(T *const y)
{
    constexpr size_t lgn = ceiled_lg(N);
    static uint32_t r[N];
    if (!r[1])
    {
        for (size_t i = 1; i < N; ++i)
            r[i] = (r[i >> 1] >> 1) + ((i & 1) << (lgn - 1));
    }
    for (size_t i = 1; i < N; ++i)
        if (i < r[i])
            swap(y[i], y[r[i]]);
}

template <size_t N, typename T>
void fft(complex<T> *const y)
{
    constexpr size_t lgn = ceiled_lg(N);
    bit_reverse<N, complex<T>>(y);
    for (size_t k = 0; k < lgn; ++k)
    {
        size_t const m = 1 << k;
        complex<T> const omega_m = polar(1.0, M_PI / m);
        for (size_t i = 0; i < N; i += m << 1)
        {
            complex<T> omega = 1.0;
            for (size_t j = i; j < i + m; ++j)
            {
                complex<T> const u = y[j], v = y[j + m] * omega;
                y[j] = u + v;
                y[j + m] = u - v;
                omega *= omega_m;
            }
        }
    }
}

template <size_t N, typename T>
void ifft(complex<T> *const y)
{
    constexpr size_t lgn = ceiled_lg(N);
    bit_reverse<N, complex<T>>(y);
    for (size_t k = 0; k < lgn; ++k)
    {
        size_t const m = 1 << k;
        complex<T> const omega_m = polar(1.0, -M_PI / m);
        for (size_t i = 0; i < N; i += m << 1)
        {
            complex<T> omega = 1.0;
            for (size_t j = i; j < i + m; ++j)
            {
                complex<T> const u = y[j], v = y[j + m] * omega;
                y[j] = u + v;
                y[j + m] = u - v;
                omega *= omega_m;
            }
        }
    }
    for (size_t i = 0; i < N; ++i)
        y[i] /= N;
}

template <size_t N, typename T>
void convolution(complex<T> *const x, complex<T> *const y, complex<T> *const z)
{
    fft<N, T>(x);
    fft<N, T>(y);
    for (size_t i = 0; i < N; ++i)
        z[i] = x[i] * y[i];
    ifft<N, T>(z);
}