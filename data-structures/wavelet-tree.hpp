#include <bits/stdc++.h>
using namespace std;

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

    int map_left(unsigned node, int i)
    {
        return t[node].x[i] - 1;
    }

    int map_right(unsigned node, int i)
    {
        return i - t[node].x[i];
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
};