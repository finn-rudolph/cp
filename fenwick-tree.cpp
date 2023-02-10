#include <bits/stdc++.h>
using namespace std;

// A standard one-dimensional Fenwick Tree plus one supporting range updates
// and range queries.

template <typename T>
struct FenwickTree
{
    vector<T> t;

    FenwickTree() {}

    FenwickTree(size_t n)
    {
        t = vector<T>(n, 0);
    }

    T prefix_query(ptrdiff_t i)
    {
        i++;
        T x = 0;
        while (i)
        {
            x += t[i - 1];
            i -= i & -i;
        }
        return x;
    }

    T range_query(ptrdiff_t i, ptrdiff_t j)
    {
        return prefix_query(j) - (i ? prefix_query(i - 1) : 0);
    }

    void increment(ptrdiff_t i, T x)
    {
        i++;
        while ((size_t)i <= t.size())
        {
            t[i - 1] += x;
            i += i & -i;
        }
    }

    void set(ptrdiff_t i, T x)
    {
        increment(i, x - range_query(i, i));
    }
};

template <typename T>
struct FenwickTreeRURQ
{
    array<FenwickTree<T>, 2> t;

    FenwickTreeRURQ() {}

    FenwickTreeRURQ(size_t n)
    {
        t[0] = FenwickTree<T>(n);
        t[1] = FenwickTree<T>(n);
    }

    T prefix_query(ptrdiff_t i)
    {
        return t[0].prefix_query(i) * (i + 1) - t[1].prefix_query(i);
    }

    T range_query(ptrdiff_t i, ptrdiff_t j)
    {
        return prefix_query(j) - (i ? prefix_query(i - 1) : 0);
    }

    void suffix_increment(ptrdiff_t i, T x)
    {
        t[0].increment(i, x);
        t[1].increment(i, x * i);
    }

    void increment(ptrdiff_t i, ptrdiff_t j, T x)
    {
        suffix_increment(i, x);
        if ((size_t)j + 1 < t[0].t.size())
            suffix_increment(j + 1, -x);
    }
};