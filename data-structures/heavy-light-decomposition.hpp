#include <bits/stdc++.h>
#include "fenwick-tree.hpp"
using namespace std;

/*
Heavy-Light-Decomposition for node update and path sum in O(log n) time per
query. The adjacency list of the tree must be given to the constructor.
*/

template <typename T>
struct Hld
{
    // root: Topmost node of the heavy path the node lies in.
    // ind: The index of a node in the Fenwick Tree.
    vector<unsigned> height, parent, heavy, root, ind;
    FenwickTree<T> t;

    Hld(vector<vector<unsigned>> const &g)
    {
        height = vector<unsigned>(g.size());
        parent = vector<unsigned>(g.size(), UINT_MAX);
        heavy = vector<unsigned>(g.size(), UINT_MAX);
        root = vector<unsigned>(g.size());
        ind = vector<unsigned>(g.size());
        t = FenwickTree<T>(g.size());

        height[0] = 0;
        find_heavy(g, 0);
        unsigned z = 0;

        // Traverse all heavy paths and set the topmost node as well as the
        // position in the Fenwick Tree. If not only all heavy paths but also
        // all subtrees shall lie in a contiguous range, process the nodes in
        // DFS order, where the DFS visits a heavy child first.
        for (unsigned i = 0; i < g.size(); i++)
            // A light child is always the root of a heavy path.
            if (parent[i] == UINT_MAX || heavy[parent[i]] != i)
            {
                unsigned j = i;
                while (j != UINT_MAX)
                {
                    root[j] = i, ind[j] = z++;
                    j = heavy[j];
                }
            }
    }

    unsigned find_heavy(vector<vector<unsigned>> const &g, unsigned u)
    {
        unsigned max_size = 0, total_size = 1;
        for (unsigned const &v : g[u])
            if (v != parent[u])
            {
                parent[v] = u;
                height[v] = height[u] + 1;
                unsigned s = find_heavy(g, v);
                if (s > max_size)
                    max_size = s, heavy[u] = v;
                total_size += s;
            }

        return total_size;
    }

    void update_node(unsigned u, T x)
    {
        t.set(ind[u], x);
    }

    T path_query(unsigned u, unsigned v)
    {
        T x = 0;
        // Move u and v up along O(log n) heavy paths to their LCA.
        while (root[u] != root[v])
        {
            if (height[root[u]] < height[root[v]])
                swap(u, v);
            x += t.range_query(ind[root[u]], ind[u]);
            u = parent[root[u]]; // Skip the light edge between heavy paths.
        }
        if (height[u] < height[v])
            swap(u, v);
        x += t.range_query(ind[v], ind[u]);
        return x;
    }
};