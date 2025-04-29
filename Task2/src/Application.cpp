#include "Application.h"

#include <algorithm>

using trianglePoints = std::array<vec2, 3>;

bool isSeparatingAxis(const trianglePoints& tri1, const trianglePoints& tri2, float axisX, float axisY) {
    auto project = [axisX, axisY](const vec2& p) { return axisX * p.x + axisY * p.y; };

    auto [min1, max1] = std::minmax({project(tri1[0]), project(tri1[1]), project(tri1[2])});
    auto [min2, max2] = std::minmax({project(tri2[0]), project(tri2[1]), project(tri2[2])});

    return (max1 < min2) || (max2 < min1);
}

bool isColliding(const triangle& t1, const triangle& t2) {
    // Test axes perpendicular to all edges of t1
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        float edgeX = t1.points[next].x - t1.points[i].x;
        float edgeY = t1.points[next].y - t1.points[i].y;
        float axisX = edgeY;
        float axisY = -edgeX;

        if (isSeparatingAxis(t1.points, t2.points, axisX, axisY)) return false;  // Separating axis found
    }

    // Test axes perpendicular to all edges of t2
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        float edgeX = t2.points[next].x - t2.points[i].x;
        float edgeY = t2.points[next].y - t2.points[i].y;
        float axisX = edgeY;
        float axisY = -edgeX;

        if (isSeparatingAxis(t1.points, t2.points, axisX, axisY)) return false;  // Separating axis found
    }

    // No separating axis found => triangles are colliding
    return true;
}
