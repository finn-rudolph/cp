#include <bits/stdc++.h>
using namespace std;

// A Segment Tree capable of maintaining the (concave downward) convex hull of
// some set of linear functions f_1, f_2 ... . You can insert new functions and
// query min(f_1(x), f_2(x), ...). Runs in O(log |D|) per query, where D is
// the domain of the functions.

template <typename T>
struct LinearFn
{
    T m, t;

    LinearFn() {}

    LinearFn(T m_, T t_) { m = m_, t = t_; }

    T operator()(T x) const { return m * x + t; }
};

template <typename T>
struct LiChaoNode
{
    LiChaoNode<T> *left, *right;
    LinearFn<T> f;

    LiChaoNode()
    {
        left = right = 0;
        // If function values go higher, change the default maximum.
        f = LinearFn<T>(0, numeric_limits<T>::max() / 4);
    }

    void insert(LinearFn<T> g, T l, T r)
    {
        T mid = (l + r) / 2;
        if (g(mid) < f(mid))
            swap(f, g);
        if (r - l == 1)
            return;
        if ((f(l) < g(l)) ^ (f(mid) < g(mid)))
        {
            if (!left)
                left = new LiChaoNode();
            left->insert(g, l, (l + r) / 2);
        }
        else
        {
            if (!right)
                right = new LiChaoNode();
            right->insert(g, (l + r) / 2, r);
        }
    }

    T get_min(T x, T l, T r)
    {
        T y = f(x);
        if (left)
            y = min(y, left->get_min(x, l, (l + r) / 2));
        if (right)
            y = min(y, right->get_min(x, (l + r) / 2, r));
        return y;
    }

    void destroy()
    {
        if (left)
            left->destroy();
        if (right)
            right->destroy();
        delete left;
        delete right;
    }
};