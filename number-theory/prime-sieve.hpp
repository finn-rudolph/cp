#include <bits/stdc++.h>
using namespace std;

/*
Returns a vector containing at each index some prime factor of the index (the
index itself for prime indices). Running time: O(n log n). The prime
factorization of any number <= n can be obtained in O(log n) from the returned
vector.
*/

template <typename T>
vector<T> prime_sieve(T n)
{
    vector<T> v(n + 1, 1);
    for (T i = 2; i <= n; i++)
        if (v[i] == 1)
            for (T j = 2 * i; j <= n; j += i)
                v[j] = i;
    return v;
};