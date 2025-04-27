#pragma once

#include <vector>

struct triangle;
struct Vector2;

class Visualisation {
public:
  explicit Visualisation(const int width, const int height, int fps = 60);
  ~Visualisation();
  bool redLight = false;

  void handleInput();
  void draw() const;
  void addTriangle(triangle &t);
  bool shouldExit() const;

private:
  bool isMouseInsideTriangle(const triangle &t, Vector2 pt);
  void drawTriangles() const;

private:
  std::vector<triangle *> triangles;
  triangle *Carrying = nullptr;
};
