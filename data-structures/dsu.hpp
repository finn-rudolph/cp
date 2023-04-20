#include <bits/stdc++.h>
using namespace std;

template <size_t N>
struct Dsu
{
    int64_t p[N];

    Dsu(size_t n) { p = vector<int64_t>(n, -1); }

    int64_t repr(int64_t u) { return p[u] < 0 ? u : p[u] = repr(p[u]); }

    bool merge(int64_t i, int64_t j)
    {
        i = repr(i);
        j = repr(j);
        if (i == j)
            return 0;

        if (p[i] > p[j])
            swap(i, j);
        p[i] += p[j];
        p[j] = i;
        return 1;
    }

    bool same_set(int64_t i, int64_t j) { return repr(i) == repr(j); }

    int64_t set_size(int64_t i) { return -p[repr(i)]; }

    void reset() { fill(p.begin(), p.end(), -1); }
};
