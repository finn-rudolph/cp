#include <bits/stdc++.h>
using namespace std;

/*
Computes two arrays containing for each index the length of the longest odd (0)
and even (1) palindrome with this index as the center. In case of even
palindromes, the center for index i is between i and i + 1.
*/

void manacher(string const &s, size_t pal[][2])
{
    for (size_t k = 0, c = 0, r = 0; k < 2; ++k, c = r = 0)
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (i < r)
                pal[i][k] = min(r - i, pal[(c << 1) - i][k]);
            while (i + pal[i][k] + k < s.size() && i - pal[i][k] < s.size() &&
                   s[i + pal[i][k] + k] == s[i - pal[i][k]])
                ++pal[i][k];
            if (i + pal[i][k] > r)
                c = i, r = i + pal[i][k];
        }
}
