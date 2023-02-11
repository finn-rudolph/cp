#include <bits/stdc++.h>
using namespace std;

/*
An arbitrary-dimensional Fenwick Tree for point update range query, as well
as for range update range query. A range is specified by two arrays i and j,
where i contains the lower and j the upper limit for each dimension (inclusive,
0-indexed).
Point update range query runs in O(log n_1 * log n_2 * ... * log n_d) per query,
where n_i is the size of the i-th dimension and d the number of dimensions.
Range update range query takes O(4^d * log n_1 * log n_2 * ... * log n_d) time.
*/

template <typename T, size_t D>
struct FenwickTree
{
    vector<T> t;
    array<size_t, D> n, l; // Dimension sizes and suffix dimension size products

    FenwickTree() {}

    FenwickTree(array<size_t, D> const &_n)
    {
        n = _n;
        l[D - 1] = 1;
        for (size_t i = D - 1; i; i--)
            l[i - 1] = l[i] * n[i];
        t = vector<T>(l[0] * n[0], 0);
    }

    T prefix_query(array<int64_t, D> i, size_t d = 0, size_t ind = 0)
    {
        if (d == D)
            return t[ind];

        i[d]++;
        T x = 0;
        while (i[d])
        {
            x += prefix_query(i, d + 1, ind + (i[d] - 1) * l[d]);
            i[d] -= i[d] & -i[d];
        }
        return x;
    }

    T range_query(array<int64_t, D> const &i, array<int64_t, D> const &j)
    {
        T x = prefix_query(j);
        size_t u = 0;
        for (size_t d = 0; d < D; d++)
            u ^= (1ULL << d) * (bool)i[d];

        for (size_t v = u; v; v = (v - 1) & u)
        {
            array<int64_t, D> query_vector;
            for (size_t d = 0; d < D; d++)
                query_vector[d] = (v & (1ULL << d)) ? i[d] - 1 : j[d];
            x += prefix_query(query_vector) * ((popcount(v) & 1) ? -1 : 1);
        }

        return x;
    }

    void increment(array<int64_t, D> i, T x, size_t d = 0, size_t ind = 0)
    {
        if (d == D)
        {
            t[ind] += x;
            return;
        }

        i[d]++;
        while ((size_t)i[d] <= n[d])
        {
            increment(i, x, d + 1, ind + (i[d] - 1) * l[d]);
            i[d] += i[d] & -i[d];
        }
    }

    void set(array<int64_t, D> const &i, T x)
    {
        increment(i, x - range_query(i, i));
    }
};

template <typename T, size_t D>
struct FenwickTreeRURQ
{
    array<FenwickTree<T, D>, 1ULL << D> t;
    array<size_t, D> n;

    FenwickTreeRURQ() {}

    FenwickTreeRURQ(array<size_t, D> const &_n)
    {
        n = _n;
        for (size_t i = 0; i < 1ULL << D; i++)
            t[i] = FenwickTree<T, D>(n);
    }

    T prefix_query(array<int64_t, D> const &i)
    {
        T x = 0;
        for (size_t v = 0; v < 1ULL << D; v++)
        {
            int64_t coefficient = (popcount(v) & 1) ? -1 : 1;
            for (size_t d = 0; d < D; d++)
                coefficient *= (v & (1ULL << d)) ? 1 : i[d] + 1;
            x += t[v].prefix_query(i) * coefficient;
        }
        return x;
    }

    T range_query(array<int64_t, D> const &i, array<int64_t, D> const &j)
    {
        T x = prefix_query(j);
        size_t u = 0;
        for (size_t d = 0; d < D; d++)
            u ^= (1ULL << d) * (bool)i[d];

        for (size_t v = u; v; v = (v - 1) & u)
        {
            array<int64_t, D> query_vector;
            for (size_t d = 0; d < D; d++)
                query_vector[d] = (v & (1ULL << d)) ? i[d] - 1 : j[d];
            x += prefix_query(query_vector) * ((popcount(v) & 1) ? -1 : 1);
        }

        return x;
    }

    void suffix_increment(array<int64_t, D> const &i, T x)
    {
        for (size_t v = 0; v < 1ULL << D; v++)
        {
            int64_t coefficient = 1;
            for (size_t d = 0; d < D; d++)
                coefficient *= (v & (1ULL << d)) ? i[d] : 1;
            t[v].increment(i, x * coefficient);
        }
    }

    void increment(array<int64_t, D> const &i, array<int64_t, D> const &j, T x)
    {
        suffix_increment(i, x);
        size_t u = 0;
        for (size_t d = 0; d < D; d++)
            u ^= (1ULL << d) * ((size_t)j[d] + 1 < n[d]);

        for (size_t v = u; v; v = (v - 1) & u)
        {
            array<int64_t, D> query_vector;
            for (size_t d = 0; d < D; d++)
                query_vector[d] = (v & (1ULL << d)) ? j[d] + 1 : i[d];
            suffix_increment(query_vector, x * ((popcount(v) & 1) ? -1 : 1));
        }
    }
};