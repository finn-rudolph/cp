#include <bits/stdc++.h>
using namespace std;

/*
An arbitrary-dimensional Fenwick Tree for point update range query, as well
as for range update range query. Everything is 0-indexed.
Point update range query runs in O(log n_1 * log n_2 * ... * log n_d) per query,
where n_i is the size of the i-th dimension and d the number of dimensions.
Range update range query takes O(4^d * log n_1 * log n_2 * ... * log n_d) time.
*/

template <typename T, int64_t... Ns>
struct FenwickTree
{
    T t = 0;
    void increment(T x) { t += x; }
    T rangeSum() { return t; }
};

template <typename T, int64_t N, int64_t... Ns>
struct FenwickTree<T, N, Ns...>
{
    FenwickTree<T, Ns...> t[N];

    template <typename... Args>
    void increment(int64_t i, Args... a)
    {
        ++i;
        while (i <= N)
            t[i - 1].increment(a...), i += i & -i;
    }

    template <typename... Args>
    T rangeSum(int64_t i, int64_t j, Args... a)
    {
        T x = 0;
        ++j;
        while (j)
            x += t[j - 1].rangeSum(a...), j -= j & -j;
        while (i)
            x -= t[i - 1].rangeSum(a...), i -= i & -i;
        return x;
    }
};

template <typename T, int64_t... Ns>
struct FenwickTreeRURQ
{
    T t = 0;
    void increment(T x) { t += x; }
    T rangeSum() { return t; }
};

template <typename T, int64_t N, int64_t... Ns>
struct FenwickTreeRURQ<T, N, Ns...>
{
    FenwickTreeRURQ<T, Ns...> t[2][N];

    template <typename... Args>
    void suffixIncrement(T x, int64_t i, Args... args)
    {
        int64_t k = i + 1;
        while (k <= N)
        {
            t[0][k - 1].increment(x, args...);
            t[1][k - 1].increment(x * (T)i, args...);
            k += k & -k;
        }
    }

    template <typename... Args>
    void increment(T x, int64_t i, int64_t j, Args... args)
    {
        suffixIncrement(x, i, args...);
        suffixIncrement(-x, j + 1, args...);
    }

    template <typename... Args>
    T prefixSum(int64_t i, Args... args)
    {
        T x = 0;
        int64_t k = i + 1;
        while (k)
        {
            x += (T)(i + 1) * t[0][k - 1].rangeSum(args...);
            x -= t[1][k - 1].rangeSum(args...);
            k -= k & -k;
        }
        return x;
    }

    template <typename... Args>
    T rangeSum(int64_t i, int64_t j, Args... args)
    {
        return prefixSum(j, args...) - (i ? prefixSum(i - 1, args...) : 0);
    }
};