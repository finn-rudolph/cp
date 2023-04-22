#include <bits/stdc++.h>
using namespace std;

template <size_t N>
struct Lca
{
    static constexpr size_t LGN = bit_ceil(N) + 1;
    unsigned anc[N][LGN], height[N];

    Lca() {}
    Lca(vector<unsigned> *tree, unsigned root)
    {
        memset(anc, 255, sizeof anc);
        height[root] = 0;
        traverse(tree, root, -1);
    }

    void traverse(vector<unsigned> *tree, unsigned u, unsigned p)
    {
        for (unsigned const &v : tree[u])
            if (v != p)
            {
                anc[v][0] = u;
                height[v] = height[u] + 1;
                for (size_t i = 1; i < LGN && anc[v][i - 1] != UINT_MAX; ++i)
                    anc[v][i] = anc[anc[v][i - 1]][i - 1];
                traverse(tree, v, u);
            }
    }

    unsigned lift(unsigned u, unsigned h)
    {
        unsigned z = 0;
        while (h)
        {
            if (h & 1)
                u = anc[u][z];
            h >>= 1;
            ++z;
        }
        return u;
    }

    unsigned lca(unsigned u, unsigned v)
    {
        if (height[u] < height[v])
            swap(u, v);
        u = lift(u, height[u] - height[v]);
        if (u == v)
            return u;
        for (size_t i = LGN - 1; i < LGN; --i)
            if (anc[u][i] != anc[v][i])
                u = anc[u][i], v = anc[v][i];
        return anc[u][0];
    }
};
