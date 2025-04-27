#include "Application.h"
#include <algorithm>
#include <array>

bool isSeparatingAxis(const std::array<vec2, 3> tri1,
                      const std::array<vec2, 3> tri2, float axisX,
                      float axisY) {
  float min1 = axisX * tri1[0].x + axisY * tri1[0].y;
  float max1 = min1;
  for (int i = 1; i < 3; ++i) {
    float proj = axisX * tri1[i].x + axisY * tri1[i].y;
    min1 = std::min(min1, proj);
    max1 = std::max(max1, proj);
  }

  float min2 = axisX * tri2[0].x + axisY * tri2[0].y;
  float max2 = min2;
  for (int i = 1; i < 3; ++i) {
    float proj = axisX * tri2[i].x + axisY * tri2[i].y;
    min2 = std::min(min2, proj);
    max2 = std::max(max2, proj);
  }

  return (max1 < min2) || (max2 < min1);
}

bool isColliding(const triangle &t1, const triangle &t2) {
  // Testujemy osie normalne do wszystkich krawędzi
  for (int i = 0; i < 3; ++i) {
    int next = (i + 1) % 3;
    // Krawędź t1
    float edgeX = t1.points[next].x - t1.points[i].x;
    float edgeY = t1.points[next].y - t1.points[i].y;
    // Normalna do krawędzi
    float axisX = edgeY;
    float axisY = -edgeX;
    if (isSeparatingAxis(t1.points, t2.points, axisX, axisY)) {
      return false; // Znaleziono oś separującą
    }
  }
  for (int i = 0; i < 3; ++i) {
    int next = (i + 1) % 3;
    // Krawędź t2
    float edgeX = t2.points[next].x - t2.points[i].x;
    float edgeY = t2.points[next].y - t2.points[i].y;
    float axisX = edgeY;
    float axisY = -edgeX;
    if (isSeparatingAxis(t1.points, t2.points, axisX, axisY)) {
      return false; // Znaleziono oś separującą
    }
  }
  // Nie znaleziono osi separującej => trójkąty nachodzą
  return true;
}
