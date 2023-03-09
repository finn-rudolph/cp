#include <bits/stdc++.h>
using namespace std;

/*
Generic functions for geometry problems, based on complex numbers.
*/

template <typename T>
T sign(T const &x) { return (x > 0) - (x < 0); }

template <typename T>
T dot_product(complex<T> const &a, complex<T> const &b)
{
    return (a * conj(b)).real();
}

template <typename T>
T cross_product(complex<T> const &a, complex<T> const &b)
{
    return (conj(a) * b).imag();
}

template <typename T> // Lines a and b are specified by two points.
complex<T> line_intersection(
    complex<T> const &a1, complex<T> const &a2, complex<T> const &b1,
    complex<T> const &b2)
{
    return a1 + (a2 - a1) * cross_product(b1 - a1, b2 - b1) /
                    cross_product(a2 - a1, b2 - b1);
}

template <typename T> // Returns 2 * the signed area of the given polygon.
T polygon_area(vector<complex<T>> const &polygon)
{
    T area = 0;
    for (size_t i = 0; i < polygon.size(); i++)
        area += cross_product(polygon[i], polygon[(i + 1) % polygon.size()]);
    return area;
}