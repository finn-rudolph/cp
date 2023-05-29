#include <bits/stdc++.h>
using namespace std;

/*
Modular inverse via binary exponentiation.
*/

template <typename T>
T binary_exp(T x, T y)
{
    T z = 1;

    while (y)
    {
        if (y & 1)
            z = (z * x) % Mod;
        x = (x * x) % Mod;
        y >>= 1;
    }

    return z;
}

template <typename T>
T modular_inverse(T x) { return binary_exp(x, Mod - 2); }

/*
Modular inverse via extended euclidean algorithm, also works for composite
(but coprime) moduli.
*/

template <typename T>
tuple<T, T, T> extended_euclid(T a, T b)
{
    if (!b)
        return {a, 1, 0};
    auto const [g, s, t] = extended_euclid(b, a % b);
    return {g, t, (s - (a / b * t) % Mod + Mod) % Mod};
}

template <typename T>
T modular_inverse(T x) { return get<1>(extended_euclid(x, Mod)); }