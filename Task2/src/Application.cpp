#include "Application.h"

#include <algorithm>

using trianglePoints = std::array<vec2, 3>;

inline bool isSeparatingAxis(const trianglePoints& tri1, const trianglePoints& tri2, vec2 axis) {
    auto project = [axis](const vec2& p) { return axis.x * p.x + axis.y * p.y; };

    auto [min1, max1] = std::minmax({project(tri1[0]), project(tri1[1]), project(tri1[2])});
    auto [min2, max2] = std::minmax({project(tri2[0]), project(tri2[1]), project(tri2[2])});

    return (max1 < min2) || (max2 < min1);
}

vec2 computeNormal(const vec2& p1, const vec2& p2) {
    float edgeX = p2.x - p1.x;
    float edgeY = p2.y - p1.y;
    return {edgeY, -edgeX};
}

bool isColliding(const triangle& t1, const triangle& t2) {
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;

        vec2 axis1 = computeNormal(t1.points[next], t1.points[i]);
        if (isSeparatingAxis(t1.points, t2.points, axis1)) return false;

        vec2 axis2 = computeNormal(t2.points[next], t2.points[i]);
        if (isSeparatingAxis(t1.points, t2.points, axis2)) return false;
    }
    return true;
}
