#include "PolygonRotation.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

double PolygonRotation::getVolume(std::vector<int> x, std::vector<int> y) {
    // Seperate positive and negative points.
    std::vector<Point> pos;
    std::vector<Point> neg;
    for (size_t i = 0; i < x.size(); i++) {
        std::vector<Point> &list = x[i] >= 0 ? pos : neg;
        double abs_x = (double)abs(x[i]);

        auto it = std::find_if(list.begin(), list.end(), [&](const Point &p) { return p.y == y[i]; });
        if (it == list.end()) {
            list.push_back({abs_x, (double)y[i]});
        } else {
            it->x = fmax(it->x, abs_x);
        }
    }

    std::vector<Point> merged;
    std::sort(pos.begin(), pos.end(), [](const Point &p1, const Point &p2) { return p1.y > p2.y; });
    std::sort(neg.begin(), neg.end(), [](const Point &p1, const Point &p2) { return p1.y > p2.y; });

    // Check for crossing points.
    if (pos.size() >= 2 && neg.size() >= 2) {
        for (size_t i = 0; i < pos.size() - 1; i++) {
            for (size_t j = 0; j < neg.size() - 1; j++) {
                Point *r = getIntersection({pos[i], pos[i + 1]}, {neg[j], neg[j + 1]});
                if (!r) continue;

                merged.push_back(*r);
                delete r;
            }
        }
    }

    // Get greater x point of all points for each y.
    for (const auto &p : pos) {
        auto it = std::find_if(merged.begin(), merged.end(), [&](const Point &mp) { return mp.y == p.y; });
        if (it == merged.end()) {
            merged.push_back(p);
        } else {
            it->x = fmax(it->x, p.x);
        }
    }

    for (const auto &p : neg) {
        auto it = std::find_if(merged.begin(), merged.end(), [&](const Point &mp) { return mp.y == p.y; });
        if (it == merged.end()) {
            merged.push_back(p);
        } else {
            it->x = fmax(it->x, p.x);
        }
    }

    // Calculate result.
    double volume = 0;
    auto frustum = [](double r1, double r2, double h) {
        return (1.0 / 3.0) * M_PI * h * (pow(r1, 2) + pow(r2, 2) + r1 * r2);
    };

    std::sort(merged.begin(), merged.end(), [](const Point &p1, const Point &p2) { return p1.y > p2.y; });
    if (merged.size() >= 2) {
        for (size_t i = 0; i < merged.size() - 1; i++) {
            Point *p1 = &merged[i];
            Point *p2 = &merged[i + 1];
            volume += frustum(p1->x, p2->x, p1->y - p2->y);
        }
    }

    return volume;
}

PolygonRotation::Point *PolygonRotation::getIntersection(Line l1, Line l2) {
    // For the purposes of this problem, we do not have to worry about
    // either line being vertical, i.e. having an undefined slope.

    // Find m and b.
    double l1_m = (l1.p2.y - l1.p1.y) / (l1.p2.x - l1.p1.x);
    double l1_b = l1.p1.y - l1_m * l1.p1.x;

    double l2_m = (l2.p2.y - l2.p1.y) / (l2.p2.x - l2.p1.x);
    double l2_b = l2.p1.y - l2_m * l2.p1.x;

    // Parallel (use epsilon comparison for floating point).
    if (fabs(l1_m - l2_m) < std::numeric_limits<double>::epsilon()) {
        return nullptr;
    }

    // Find x and y.
    double x = (l2_b - l1_b) / (l1_m - l2_m);
    double y = l1_m * x + l1_b;

    return new Point(x, y);
}
