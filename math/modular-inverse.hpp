#include <bits/stdc++.h>
using namespace std;

template <typename T>
T binary_exp(T x, T y, T m)
{
    T z = 1;

    while (y)
    {
        if (y & 1)
            z = (z * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }

    return z;
}

template <typename T>
T mod_inv(T x, T m) { return binary_exp(x, m - 2, m); }

template <typename T>
tuple<T, T, T> extended_euclid(T a, T b)
{
    if (!b)
        return {a, 1, 0};
    auto const [g, s, t] = extended_euclid(b, a % b);
    return {g, t, s - a / b * t};
}