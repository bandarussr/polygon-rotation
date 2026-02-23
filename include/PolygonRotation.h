#pragma once
#include <vector>

class PolygonRotation {
public:
    static double getVolume(std::vector<int> x, std::vector<int> y);

private:
    struct Point {
        Point(double x, double y) : x(x), y(y) {}
        double x;
        double y;
    };

    struct Line {
        Line(Point p1, Point p2) : p1(p1), p2(p2) {}
        Point p1;
        Point p2;
    };

    static Point *getIntersection(Line l1, Line l2);
};
