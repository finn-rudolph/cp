#include <bits/stdc++.h>
#include "fenwick-tree.hpp"
using namespace std;

/*
Heavy-Light-Decomposition for node update, path sum and subtree sum in
O(log^2 n) time per query.
*/

template <typename T, size_t N>
struct Hld
{
    vector<unsigned> g[N];
    unsigned height[N], parent[N], root[N], ind[N], subtree_size[N];
    FenwickTree<T, N> t;

    void init() { find_subtree_size(0), build_heavy_paths(0, 0); }

    void find_subtree_size(unsigned u)
    {
        subtree_size[u] = 1;
        for (auto &v : g[u])
            if (v != parent[u])
            {
                parent[v] = u;
                height[v] = height[u] + 1;
                find_subtree_size(v);
                subtree_size[u] += subtree_size[v];
                if (subtree_size[v] > subtree_size[g[u][0]] || g[u][0] == parent[u])
                    swap(g[u][0], v);
            }
    }

    unsigned build_heavy_paths(unsigned u, unsigned i)
    {
        ind[u] = i++;
        for (auto const &v : g[u])
            if (v != parent[u])
            {
                root[v] = (v == g[u][0] ? root[u] : v);
                i = build_heavy_paths(v, i);
            }
        return i;
    }

    void update_node(unsigned u, T x)
    {
        t.increment(ind[u], x);
    }

    T path_sum(unsigned u, unsigned v)
    {
        T x = 0;
        // Move u and v up along O(log n) heavy paths to their LCA.
        while (root[u] != root[v])
        {
            if (height[root[u]] < height[root[v]])
                swap(u, v);
            x += t.range_sum(ind[root[u]], ind[u]);
            u = parent[root[u]]; // Skip the light edge between heavy paths.
        }
        if (height[u] < height[v])
            swap(u, v);
        x += t.range_sum(ind[v], ind[u]);
        return x;
    }
};