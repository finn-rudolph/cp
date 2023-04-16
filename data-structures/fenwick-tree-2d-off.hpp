#include <bits/stdc++.h>
using namespace std;

/*
A 2D Fenwick Tree allowing Point Update Range Query when the Query coordinates
are known in advance. O(n log^2 n) time per query, O(n log n) memory. M must
be greater or equal than the sum of sizes of all Fenwick Trees (usually around
n log n).
*/

template <typename T, int64_t N, int64_t M>
struct FenwickTree2dOff
{
    T t[M];
    vector<pair<unsigned, unsigned>> coords;
    unsigned b[N + 1], c[M];

    void add_coordinate(int64_t i, int64_t j) { coords.emplace_back(i, j); }

    void initialize()
    {
        sort(coords.begin(), coords.end(), [](auto const &a, auto const &b)
             { return a.second < b.second; });
        memset(t, 255, N * sizeof *t);
        for (auto const &[x, y] : coords)
            for (int64_t i = x + 1; i <= N; i += i & -i)
                b[i - 1] += (t[i - 1] != y), t[i - 1] = y;
        for (size_t i = 1; i < N; ++i)
            b[i] += b[i - 1];
        memset(t, 255, N * sizeof *t);
        for (auto const &[x, y] : views::reverse(coords))
            for (int64_t i = x + 1; i <= N; i += i & -i)
                if (t[i - 1] != y)
                    c[--b[i - 1]] = y, t[i - 1] = y;
        memset(t, 0, N * sizeof *t);
    }

    void update(int64_t i, int64_t j, T x)
    {
        ++i;
        while (i <= N)
        {
            int64_t k = upper_bound(c + b[i - 1], c + b[i], j) - (c + b[i - 1]);
            while (k <= b[i] - b[i - 1])
                t[b[i - 1] + k - 1] += x, k += k & -k;
            i += i & -i;
        }
    }

    T prefix_sum(int64_t i, int64_t j)
    {
        ++i;
        T x = 0;
        while (i)
        {
            int64_t k = upper_bound(c + b[i - 1], c + b[i], j) - (c + b[i - 1]);
            while (k)
                x += t[b[i - 1] + k - 1], k -= k & -k;
            i -= i & -i;
        }
        return x;
    }

    T range_sum(int64_t i1, int64_t i2, int64_t j1, int64_t j2)
    {
        return prefix_sum(i2, j2) - (i1 ? prefix_sum(i1 - 1, j2) : 0) -
               (j1 ? prefix_sum(i2, j1 - 1) : 0) +
               (i1 && j1 ? prefix_sum(i1 - 1, j1 - 1) : 0);
    }
};