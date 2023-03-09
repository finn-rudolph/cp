#include <bits/stdc++.h>
using namespace std;

/*
Allows to compute the polynomial hash of any substring in O(1) with O(n)
preprocessing. The template argument for mod should be a large prime, e. g.
10^9 + 9 or 2^61 - 1. T must be signed and able to represent mod^2.
*/

template <typename T, T Base, T Mod>
struct PolynomialHash
{
    vector<T> z, p;

    PolynomialHash(string const &s)
    {
        z = vector<T>(s.size());
        p = vector<T>(s.size());
        p[0] = 1;
        z[0] = s[0];
        for (size_t i = 1; i < s.size(); i++)
        {
            z[i] = (z[i - 1] * Base + s[i]) % Mod;
            p[i] = (p[i - 1] * Base) % Mod;
        }
    }

    T range_hash(size_t i, size_t j) // hash value in [i, j)
    {
        if (!i)
            return z[j - 1];
        return (z[j - 1] - (z[i - 1] * p[j - i]) % Mod + Mod) % Mod;
    }
};