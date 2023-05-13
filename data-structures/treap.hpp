#include <bits/stdc++.h>
using namespace std;

/*
A basic implicit treap allowing splits / merges while storing some value in
each node.
*/

mt19937 mt;

struct Treap
{
    int32_t v, l, r, subtree_size;
    uint32_t y;
    Treap() {}
    Treap(int32_t _v) { v = _v, y = mt(), l = r = -1, subtree_size = 1; }
};

Treap t[1];

int32_t get_subtree_size(int32_t node) { return node == -1 ? 0 : t[node].subtree_size; }

pair<int32_t, int32_t> split(int32_t node, int32_t k)
{
    if (node == -1)
        return {-1, -1};
    uint32_t l, r;
    if (get_subtree_size(t[node].l) <= k)
        tie(t[node].r, r) = split(t[node].r, k - get_subtree_size(t[node].l) - 1), l = node;
    else
        tie(l, t[node].l) = split(t[node].l, k), r = node;
    t[node].subtree_size = get_subtree_size(t[node].l) + get_subtree_size(t[node].r) + 1;
    return {l, r};
}

int32_t merge(int32_t l, int32_t r)
{
    if (l == -1 || r == -1)
        return l == -1 ? r : l;
    int32_t root;
    if (t[l].y > t[r].y)
        t[l].r = merge(t[l].r, r), root = l;
    else
        t[r].l = merge(l, t[r].l), root = r;
    t[root].subtree_size = get_subtree_size(t[root].l) + get_subtree_size(t[root].r) + 1;
    return root;
}