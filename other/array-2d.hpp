#include <bits/stdc++.h>
using namespace std;

/*
Some utility functions for two-dimensional arrays.
*/

template <typename T>
void rotate_c(vector<vector<T>> &y)
{
    vector<vector<T>> z(y[0].size(), vector<T>(y.size()));
    for (size_t i = 0; i < y.size(); i++)
        for (size_t j = 0; j < y[i].size(); j++)
            z[j][y.size() - i - 1] = y[i][j];
    swap(y, z);
}

template <typename T>
void rotate_cc(vector<vector<T>> &y)
{
    vector<vector<T>> z(y[0].size(), vector<T>(y.size()));
    for (size_t i = 0; i < y.size(); i++)
        for (size_t j = 0; j < y[i].size(); j++)
            z[y[i].size() - j - 1][i] = y[i][j];
    swap(y, z);
}

template <typename T>
vector<vector<T>> prefix_sum(vector<vector<T>> &y)
{
    vector<vector<T>> p(y.size(), vector<T>(y[0].size()));
    for (size_t i = 0; i < y.size(); i++)
        partial_sum(y[i].begin(), y[i].end(), p[i].begin());
    for (size_t i = 0; i < y.size() - 1; i++)
        for (size_t j = 0; j < y[i].size(); j++)
            p[i + 1][j] += p[i][j];
    return p;
}

template <typename T>
T area_sum(
    vector<vector<T>> const &prefix_sum, size_t i1, size_t j1, size_t i2,
    size_t j2)
{
    T x = prefix_sum[i2][j2];
    if (i1)
        x -= prefix_sum[i1 - 1][j2];
    if (j1)
        x -= prefix_sum[i2][j1 - 1];
    if (i1 && j1)
        x += prefix_sum[i1 - 1][j1 - 1];
    return x;
}