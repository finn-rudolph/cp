#include <bits/stdc++.h>
using namespace std;

/*
Allows to compute the polynomial hash of any substring in O(1) with O(n)
preprocessing. The template argument for Mod should be a large prime, e. g.
10^9 + 9 or 2^61 - 1. T must be signed and able to represent Mod^2.
*/

template <typename T, size_t N, T Base, T Mod>
struct PolynomialHash
{
    T z[N], p[N];

    PolynomialHash(string const &s)
    {
        p[0] = 1;
        z[0] = s[0];
        for (size_t i = 1; i < s.size(); i++)
        {
            z[i] = (z[i - 1] * Base + s[i]) % Mod;
            p[i] = (p[i - 1] * Base) % Mod;
        }
    }

    T range_hash(size_t i, size_t j) // hash value in [i, j]
    {
        if (!i)
            return z[j];
        return (z[j] - (z[i - 1] * p[j - i + 1]) % Mod + Mod) % Mod;
    }
};