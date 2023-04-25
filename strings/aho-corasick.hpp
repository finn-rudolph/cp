#include <bits/stdc++.h>
using namespace std;

/*
One of the coolest data structures out there.
*/

template <size_t N>
struct AhoCorasick
{
    unsigned ch[N][26], link[N], n;
    bitset<N> terminal;

    AhoCorasick() { memset(ch, 0, sizeof ch), link[0] = 0, n = 1; }

    void insert(string const &s)
    {
        size_t x = 0;
        for (char const &c : s)
            x = ch[x][c - 'a'] ? ch[x][c - 'a'] : ch[x][c - 'a'] = n++;
        terminal[x] = 1;
    }

    void build_suffix_links()
    {
        queue<unsigned> q({0});
        while (!q.empty())
        {
            unsigned const x = q.front();
            q.pop();
            for (size_t i = 0; i < 26; ++i)
                if (ch[x][i])
                {
                    link[ch[x][i]] = link[x];
                    while (link[ch[x][i]] && !ch[link[ch[x][i]]][i])
                        link[ch[x][i]] = link[link[ch[x][i]]];
                    link[ch[x][i]] = ch[x][i] == ch[link[ch[x][i]]][i]
                                         ? 0
                                         : ch[link[ch[x][i]]][i];
                    q.push(ch[x][i]);
                }
        }
    }
};