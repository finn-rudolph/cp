#include <bits/stdc++.h>
using namespace std;

struct BarretReduction
{
    __int128_t n, m;

    BarretReduction(int64_t const n_) { n = n_, m = ((__int128_t)1 << 64) / n; }

    int64_t operator()(__int128_t const x) const
    {
        __int128_t const y = x - ((x * m) >> 64) * n;
        return y > n ? y - n : y;
    }
};