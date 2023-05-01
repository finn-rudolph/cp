#include "candies.h"
#include <bits/stdc++.h>
using namespace std;

constexpr size_t N = 200000, L = 1 << 18;

int64_t t[2 * L][3];
tuple<size_t, int64_t, size_t> events[2 * N];

void propagate(size_t k)
{
    t[2 * k][0] += t[k][2];
    t[2 * k][1] += t[k][2];
    t[2 * k][2] += t[k][2];
    t[2 * k + 1][0] += t[k][2];
    t[2 * k + 1][1] += t[k][2];
    t[2 * k + 1][2] += t[k][2];
    t[k][2] = 0;
}

void update(size_t i, size_t j, int64_t x, size_t k = 1, size_t a = 0, size_t b = L - 1)
{
    if (b < i || a > j)
        return;
    if (i <= a && b <= j)
    {
        t[k][0] += x;
        t[k][1] += x;
        t[k][2] += x;
    }
    else
    {
        propagate(k);
        update(i, j, x, 2 * k, a, (a + b) / 2);
        update(i, j, x, 2 * k + 1, (a + b) / 2 + 1, b);
        t[k][0] = max(t[2 * k][0], t[2 * k + 1][0]);
        t[k][1] = min(t[2 * k][1], t[2 * k + 1][1]);
    }
}

int64_t get_value(size_t i)
{
    size_t k = 1, a = 0, b = L - 1;
    while (k < L)
    {
        propagate(k);
        if (i <= (a + b) / 2)
            k = 2 * k, b = (a + b) / 2;
        else
            k = 2 * k + 1, a = (a + b) / 2 + 1;
    }
    return t[k][0];
}

int64_t find_greater_suffix(int64_t c)
{
    size_t k = 1;
    int64_t suffix_max = INT64_MIN / 2, suffix_min = INT64_MAX / 2;
    while (k < L)
    {
        propagate(k);
        if (max(suffix_max, t[2 * k + 1][0]) - min(suffix_min, t[2 * k + 1][1]) >= c)
        {
            k = 2 * k + 1;
        }
        else
        {
            suffix_max = max(suffix_max, t[2 * k + 1][0]);
            suffix_min = min(suffix_min, t[2 * k + 1][1]);
            k = 2 * k;
        }
    }
    suffix_max = max(suffix_max, t[k][0]);
    suffix_min = min(suffix_min, t[k][1]);
    if (t[k][1] == suffix_min)
        return c - (suffix_max - get_value(L - 1));
    else
        return get_value(L - 1) - suffix_min;
}

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v)
{
    size_t const n = c.size(), q = l.size();
    for (size_t i = 0; i < q; ++i)
        events[2 * i] = {l[i], v[i], i}, events[2 * i + 1] = {r[i] + 1, -v[i], i};
    sort(events, events + 2 * q);
    auto it = events;
    vector<int> ans(n);
    for (size_t i = 0; i < n; ++i)
    {
        while (it != events + 2 * q && get<0>(*it) <= i)
        {
            update(get<2>(*it), L - 1, get<1>(*it));
            ++it;
        }
        if (t[1][0] - t[1][1] < c[i])
            ans[i] = get_value(L - 1) + (t[1][1] < 0 ? -t[1][1] : (t[1][0] > c[i] ? c[i] - t[1][0] : 0));
        else
            ans[i] = find_greater_suffix(c[i]);
    }
    return ans;
}
