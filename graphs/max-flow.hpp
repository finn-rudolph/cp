#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct MaxFlow
{
    vector<vector<tuple<size_t, size_t, T>>> g;
    vector<size_t> level, index;

    // g_: Graph given as an adjacency vector with pairs of (neighbor, capacity)
    MaxFlow(vector<vector<pair<size_t, T>>> const &g_)
    {
        g.resize(g_.size());
        level.resize(g_.size());
        index.resize(g_.size());
        for (size_t u = 0; u < g_.size(); u++)
            for (auto const &[v, w] : g_[u])
            {
                g[u].emplace_back(v, g[v].size(), w);
                g[v].emplace_back(u, g[u].size() - 1, 0);
            }
    }

    bool build_level_graph(size_t s, size_t t)
    {
        fill(level.begin(), level.end(), SIZE_MAX);
        fill(index.begin(), index.end(), 0);
        level[s] = 0;
        queue<size_t> q({s});
        while (!q.empty())
        {
            size_t const u = q.front();
            q.pop();
            for (auto const &[v, r, c] : g[u])
                if (c && level[v] == SIZE_MAX)
                {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        return level[t] != SIZE_MAX;
    }

    T find_augmenting_path(size_t u, T f, size_t t)
    {
        if (u == t)
            return f;
        while (index[u] < g[u].size())
        {
            auto &[v, r, c] = g[u][index[u]];
            if (c && level[v] == level[u] + 1)
            {
                T e = find_augmenting_path(v, min(f, c), t);
                if (e)
                {
                    c -= e;
                    get<2>(g[v][r]) += e;
                    return e;
                }
            }
            index[u]++;
        }
        return 0;
    }

    T run(size_t s, size_t t) // returns maximum flow value
    {
        T f = 0;
        while (build_level_graph(s, t))
            while (T e = find_augmenting_path(s, numeric_limits<T>::max(), t))
                f += e;
        return f;
    }
};