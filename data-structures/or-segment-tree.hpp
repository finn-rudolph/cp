#include <bits/stdc++.h>
using namespace std;

/*
Allows setting / unsetting bits in an array of size N (where N must be a power
of 2), as well as querying the previous / next nonzero element in O(log n) time.
This is much faster than using a std::set.
*/

template <size_t N>
struct OrSegmentTree
{
    bitset<2 * N> t;

    bool operator[](size_t i) { return t[N + i]; }
    void reset() { t.reset(); }

    void set(size_t i, bool x)
    {
        t[i += N] = x;
        while (i >>= 1)
            t[i] = t[2 * i] | t[2 * i + 1];
    }

    ptrdiff_t previousNonzero(size_t i)
    {
        i += N;
        do
        {
            if ((i & 1) && t[i - 1])
            {
                --i;
                while (i < N)
                    i = 2 * i + t[2 * i + 1];
                return i - N;
            }
        } while ((i >>= 1) > 1);
        return -1;
    }

    ptrdiff_t nextNonzero(size_t i)
    {
        i += N;
        do
        {
            if (!(i & 1) && t[i + 1])
            {
                ++i;
                while (i < N)
                    i = 2 * i + !t[2 * i];
                return i - N;
            }
        } while ((i >>= 1) > 1);
        return N;
    }
};
