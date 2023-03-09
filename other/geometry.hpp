#include <bits/stdc++.h>
using namespace std;

/*
Generic alias declarations and functions for geometry problems, based on complex
numbers.
*/

template <typename T>
using Segment = pair<complex<T>, complex<T>>;
template <typename T>
using Polygon = vector<complex<T>>;

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

// Lines a and b are specified by segments. If this function is used for
// finding a segment intersection, first check if the segments intersect.
template <typename T>
complex<T> line_intersection(Segment<T> const &a, Segment<T> const &b)
{
    return a.first + (a.second - a.first) *
                         cross_product(b.first - a.first, b.second - b.first) /
                         cross_product(a.second - a.first, b.second - b.first);
}

template <typename T, T Epsilon>
bool point_on_segment(Segment<T> const &a, complex<T> const &b)
{
    return abs(cross_product(a.second - a.first, b - a.first)) <= Epsilon &&
           min(a.first.real(), a.second.real()) <= b.real() &&
           b.real() <= max(a.first.real(), a.second.real()) &&
           min(a.first.imag(), a.second.imag()) <= b.imag() &&
           b.imag() <= max(a.first.imag(), a.second.imag());
}

// Can safely be used for integers, as no division is required. Epsilon is the
// threshold for equality for floating-point types, for integers it must be 0.
template <typename T, T Epsilon>
bool segments_intersect(Segment<T> const &a, Segment<T> const &b)
{
    T const u = cross_product(b.first - a.first, b.second - a.first),
            v = cross_product(b.first - a.second, b.second - a.second),
            w = cross_product(a.first - b.first, a.second - b.first),
            x = cross_product(a.first - b.second, a.second - b.second);
    return (sign(u) != sign(v) && sign(w) != sign(x)) ||
           point_on_segment(a, b.first) || point_on_segment(a, b.second) ||
           point_on_segment(b, a.first) || point_on_segment(b, a.second);
}

template <typename T> // Returns 2 * the signed area of the given polygon.
T polygon_area(Polygon<T> const &polygon)
{
    T area = 0;
    for (size_t i = 0; i < polygon.size(); i++)
        area += cross_product(polygon[i], polygon[(i + 1) % polygon.size()]);
    return area;
}
