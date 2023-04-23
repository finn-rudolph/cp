#include <bits/stdc++.h>
using namespace std;

/*
Data structure that maintains the palindromes of a string in a tree structure.
"link" is the pointer to the next smaller suffix palindrome, it's 0 if there is
none.
*/

template <size_t N>
struct PalindromeTree
{
    int64_t len[N], link[N], ch[N][26], cnt[N], n, x;
    string s;

    PalindromeTree()
    {
        link[0] = 1, len[1] = -1, x = len[0] = link[1] = 0, n = 2;
        s.push_back('\0');
    }

    void append(char c)
    {
        s.push_back(c);
        while (s[s.size() - len[x] - 2] != c)
            x = link[x];
        if (!ch[x][c - 'a'])
        {
            len[n] = len[x] + 2;
            link[n] = link[x];
            while (s[s.size() - len[link[n]] - 2] != s.back())
                link[n] = link[link[n]];
            link[n] = ch[link[n]][c - 'a'];
            ch[x][c - 'a'] = n++;
        }
        x = ch[x][c - 'a'];
        ++cnt[x];
    }
};
