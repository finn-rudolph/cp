#include <bits/stdc++.h>
using namespace std;

/*
Allows to compute the polynomial hash of any substring in O(1) with O(n)
preprocessing. The template argument for Mod should be a large prime, e. g.
10^9 + 9 or 2^61 - 1. T must be signed and able to represent Mod^2.
*/

template <typename T, T Base, T Mod>
struct PolynomialHash
{
    vector<T> z, p;

    PolynomialHash(string const &s)
    {
        z.resize(s.size());
        p.resize(s.size());
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

/*
Same as above but allows updating characters in O(log n), too. Queries are
O(log n).
*/

template <typename T, T Base, T Mod>
struct DynamicPolynomialHash
{
    vector<T> h, p; // hash segment tree and powers of Base
    size_t n, lgn;

    DynamicPolynomialHash(string const &s)
    {
        lgn = 32 - __builtin_clz(s.size());
        n = 1 << lgn;
        h.resize(2 * n);
        p.resize(n);

        for (size_t i = 0; i < s.size(); i++)
            h[n + i] = s[i];
        p[0] = 1;
        for (size_t i = 1; i < n; i++)
            p[i] = (p[i - 1] * Base) % Mod;
        for (size_t i = n - 1; i; i--)
            h[i] = (h[2 * i] * p[node_size(2 * i)] + h[2 * i + 1]) % Mod;
    }

    size_t node_size(size_t i) { return 1 << (lgn - 31 + __builtin_clz(i)); }

    void update(size_t i, char c)
    {
        i += n;
        h[i] = c;
        while (i >>= 1)
            h[i] = (h[2 * i] * p[node_size(2 * i)] + h[2 * i + 1]) % Mod;
    }

    T range_hash(size_t i, size_t j) // hash value in [i, j]
    {
        i += n, j += n;
        T x = 0, y = 0, y_size = 0;

        while (i <= j)
        {
            if (i & 1)
            {
                x = (x * p[node_size(i)] + h[i]) % Mod;
                i++;
            }
            if (!(j & 1))
            {
                y = (h[j] * p[y_size] + y) % Mod;
                y_size += node_size(j);
                j--;
            }
            i >>= 1;
            j >>= 1;
        }

        return (x * p[y_size] + y) % Mod;
    }
};