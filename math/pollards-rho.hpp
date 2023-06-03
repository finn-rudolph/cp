#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U> // T: single precision, U: double precision
struct Montgomery
{
    T n, r;

    constexpr Montgomery(T n) : n(n), r(1)
    {
        for (size_t i = 0; 1U << i < sizeof(T) << 3; ++i)
            r *= 2 - n * r;
    }

    T reduce(U a) const
    {
        return (a >> (sizeof(T) << 3)) + n - (((U)((T)a * r) * n) >> (sizeof(T) << 3));
    }

    T multiply(T a, T b) { return reduce((U)a * b); }

    T transform(T a) { return ((U)a << (sizeof(T) << 3)) % n; }
};

template <typename T>
T binary_gcd(T a, T b)
{
    if (!a)
        return b;
    if (!b)
        return a;
    uint32_t u = countr_zero(a), v = countr_zero(b), w = min(u, v);
    b >>= v;

    while (a)
    {
        a >>= u;
        T const d = b - a;
        u = countr_zero(d);
        b = min(a, b);
        a = min(d, ~(d - 1));
    }

    return b << w;
}

template <typename T, typename U>
T pollards_rho(T n, T seed)
{
    Montgomery<T, U> mtg(n);
    size_t const block_size = __lg(n);
    T x = seed;

    for (size_t l = block_size;; l <<= 1)
    {
        T y = x, p = 1;
        for (size_t i = 0; i < l; i += block_size)
        {
            for (size_t j = 0; j < block_size; ++j)
            {
                x = mtg.multiply(x, x) + 1;
                p = mtg.multiply(p, y > x ? y - x : x - y);
            }
            T const g = binary_gcd(p, n);
            if (g != 1)
                return g;
        }
    }
}