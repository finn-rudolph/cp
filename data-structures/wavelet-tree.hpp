#include <bits/stdc++.h>
using namespace std;

/*
A simple wavelet tree without any augmentations.
*/

template <typename T, T sigma, int L>
struct WaveletTree
{
    struct Node
    {
        unsigned l, r;
        vector<int> x;
    };

    Node t[L];

    unsigned build(vector<T> seq, T a = 0, T b = sigma)
    {
        static unsigned l = 0;

        if (seq.empty())
            return UINT_MAX;

        unsigned node = l++;
        if (a == b)
            return node;

        t[node].x.resize(seq.size());
        T const mid = (a + b) / 2;
        vector<T> left_seq, right_seq;

        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (seq[i] <= mid)
                left_seq.push_back(seq[i]), t[node].x[i] = 1;
            else
                right_seq.push_back(seq[i]);
        }
        for (size_t i = 1; i < seq.size(); ++i)
            t[node].x[i] += t[node].x[i - 1];

        t[node].l = build(left_seq, a, mid);
        t[node].r = build(right_seq, mid + 1, b);
        return node;
    }

    inline int map_left(unsigned node, int i)
    {
        return i >= 0 ? t[node].x[i] - 1 : -1;
    }

    inline int map_right(unsigned node, int i)
    {
        return i >= 0 ? i - t[node].x[i] : -1;
    }

    unsigned rank(T q, int i, unsigned node = 0, T a = 0, T b = sigma)
    {
        if (i == -1)
            return 0;
        if (a == b)
            return i + 1;

        T mid = (a + b) / 2;
        if (q <= mid)
            return rank(q, map_left(node, i), t[node].l, a, mid);
        else
            return rank(q, map_right(node, i), t[node].r, mid + 1, b);
    }

    T quantile(int i, int j, int k, unsigned node = 0, T a = 0, T b = sigma)
    {
        if (a == b)
            return a;
        int c = map_left(node, j) - map_left(node, i - 1);
        if (c >= k)
            return quantile(map_left(node, i - 1) + 1,
                            map_left(node, j), k, t[node].l, a, (a + b) / 2);
        else
            return quantile(map_right(node, i - 1) + 1,
                            map_right(node, j), k - c, t[node].r, (a + b) / 2 + 1, b);
    }

    unsigned count(int i, int j, T x, T y, unsigned node = 0, T a = 0, T b = sigma)
    {
        if (node == UINT_MAX || b < x || a > y)
            return 0;
        if (x <= a && b <= y)
            return j - i + 1;

        return count(map_left(node, i - 1) + 1, map_left(node, j), x, y, t[node].l, a, (a + b) / 2) +
               count(map_right(node, i - 1) + 1, map_right(node, j), x, y, t[node].r, (a + b) / 2 + 1, b);
    }

    void swap_adjacent(int i, unsigned node = 0)
    {
        if ((map_left(node, i + 1) - map_left(node, i - 1)) & 1)
        {
            // Element i and i + 1 are mapped to different children.
            if (map_left(node, i) != map_left(node, i - 1))
                t[node].x[i]--;
            else
                t[node].x[i]++;
        }
        else
        {
            if (map_left(node, i) != map_left(node, i - 1))
                swap_adjacent(map_left(node, i), t[node].l);
            else
                swap_adjacent(map_right(node, i), t[node].r);
        }
    }
};