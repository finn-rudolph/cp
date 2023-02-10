#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct FenwickTree2d
{
    vector<vector<T>> t;

    FenwickTree2d() {}

    FenwickTree2d(size_t n1, size_t n2)
    {
        t = vector<vector<T>>(n1, vector<T>(n2, 0));
    }

    T prefix_query(ptrdiff_t i1, ptrdiff_t i2)
    {
        i1++, i2++;
        T x = 0;
        while (i1)
        {
            ptrdiff_t u = i2;
            while (u)
            {
                x += t[i1 - 1][u - 1];
                u -= u & -u;
            }
            i1 -= i1 & -i1;
        }
        return x;
    }

    // Sum in the rectangle with corners (i1, i2) and (j1, j2).
    T range_query(ptrdiff_t i1, ptrdiff_t i2, ptrdiff_t j1, ptrdiff_t j2)
    {
        T x = prefix_query(j1, j2);
        if (i1)
            x -= prefix_query(i1 - 1, j2);
        if (i2)
            x -= prefix_query(j1, i2 - 1);
        if (i1 && i2)
            x += prefix_query(i1 - 1, i2 - 1);
        return x;
    }

    void increment(ptrdiff_t i1, ptrdiff_t i2, T x)
    {
        i1++, i2++;
        while ((size_t)i1 <= t.size())
        {
            ptrdiff_t u = i2;
            while ((size_t)u <= t[i1 - 1].size())
            {
                t[i1 - 1][u - 1] += x;
                u += u & -u;
            }
            i1 += i1 & -i1;
        }
    }

    void set(ptrdiff_t i1, ptrdiff_t i2, T x)
    {
        increment(i1, i2, x - range_query(i1, i2, i1, i2));
    }
};

template <typename T>
struct FenwickTree2dRURQ
{
    array<FenwickTree2d<T>, 4> t;

    FenwickTree2dRURQ() {}

    FenwickTree2dRURQ(size_t n1, size_t n2)
    {
        for (size_t i = 0; i < t.size(); i++)
            t[i] = FenwickTree2d<T>(n1, n2);
    }

    T prefix_query(ptrdiff_t i1, ptrdiff_t i2)
    {
        return t[0].prefix_query(i1, i2) * (i1 + 1) * (i2 + 1) -
               t[1].prefix_query(i1, i2) * (i2 + 1) -
               t[2].prefix_query(i1, i2) * (i1 + 1) +
               t[3].prefix_query(i1, i2);
    }

    T range_query(ptrdiff_t i1, ptrdiff_t i2, ptrdiff_t j1, ptrdiff_t j2)
    {
        T x = prefix_query(j1, j2);
        if (i1)
            x -= prefix_query(i1 - 1, j2);
        if (i2)
            x -= prefix_query(j1, i2 - 1);
        if (i1 && i2)
            x += prefix_query(i1 - 1, i2 - 1);
        return x;
    }

    void suffix_increment(ptrdiff_t i1, ptrdiff_t i2, T x)
    {
        t[0].increment(i1, i2, x);
        t[1].increment(i1, i2, x * i1);
        t[2].increment(i1, i2, x * i2);
        t[3].increment(i1, i2, x * i1 * i2);
    }

    void increment(ptrdiff_t i1, ptrdiff_t i2, ptrdiff_t j1, ptrdiff_t j2, T x)
    {
        suffix_increment(i1, i2, x);
        if ((size_t)j1 + 1 < t[0].t.size())
            suffix_increment(j1 + 1, i2, -x);
        if ((size_t)j2 + 1 < t[0].t[0].size())
            suffix_increment(i1, j2 + 1, -x);
        if ((size_t)j1 + 1 < t[0].t.size() && (size_t)j2 + 1 < t[0].t[0].size())
            suffix_increment(j1 + 1, j2 + 1, x);
    }
};