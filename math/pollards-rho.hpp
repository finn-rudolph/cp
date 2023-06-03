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
        return (a >> (sizeof(T) << 3)) + n - ((U)((T)a * r) * n) >> (sizeof(T) << 3);
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

template <typename T>
T pollards_rho(T n)
{
}
