#include <bits/stdc++.h>
using namespace std;

void kmp(string const &s, size_t *pi)
{
    for (size_t i = 1, j = 0; i < s.size(); ++i)
    {
        while (s[i] != s[j] && j)
            j = pi[j - 1];
        j += s[i] == s[j];
        pi[i] = j;
    }
}