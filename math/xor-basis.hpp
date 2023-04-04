#include <bits/stdc++.h>
using namespace std;

/*
Finds a basis for a given set of vectors in Z_2^d. T must be integral.
*/

template <typename T>
vector<T> xor_basis(vector<T> const &vecs, size_t d)
{
    vector<T> basis(d);
    for (T x : vecs)
        for (size_t i = 0; i < d; i++)
            if (x & ((T)1 << i))
            {
                if (!basis[i])
                {
                    basis[i] = x;
                    break;
                }
                else
                    x ^= basis[i];
            }
    auto it = basis.begin(), jt = basis.begin();
    while (jt != basis.end())
    {
        if (*jt)
            *it = *jt, ++it;
        jt++;
    }
    basis.resize(it - basis.begin());
    return basis;
}