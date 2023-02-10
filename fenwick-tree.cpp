#include <bits/stdc++.h>
using namespace std;

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
    FenwickTree<T> t1, t2;

    FenwickTreeRURQ(size_t n)
    {
        t1 = FenwickTree<T>(n);
        t2 = FenwickTree<T>(n);
    }

    void increment(ptrdiff_t i, ptrdiff_t j, T x)
    {
        t1.increment(i, x);
        t2.increment(i, x * i);
        if ((size_t)j + 1 < t1.t.size())
        {
            t1.increment(j + 1, -x);
            t2.increment(j + 1, -x * (j + 1));
        }
    }

    T prefix_query(ptrdiff_t i)
    {
        return t1.prefix_query(i) * (i + 1) - t2.prefix_query(i);
    }

    T range_query(ptrdiff_t i, ptrdiff_t j)
    {
        return prefix_query(j) - (i ? prefix_query(i - 1) : 0);
    }
};