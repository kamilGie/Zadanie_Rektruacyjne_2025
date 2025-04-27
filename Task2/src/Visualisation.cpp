#include "Visualisation.h"
#include "Application.h"
#include <raylib.h>

Visualisation::Visualisation(const int width, const int height, int fps) {
  InitWindow(width, height, "Triangles");
  SetTargetFPS(fps);
}

Visualisation::~Visualisation() { CloseWindow(); }

void Visualisation::addTriangle(triangle &t) { triangles.push_back(&t); }

void Visualisation::drawTriangles() const {
  for (triangle *t : triangles) {
    DrawTriangle(Vector2{t->points[0].x, t->points[0].y},
                 Vector2{t->points[1].x, t->points[1].y},
                 Vector2{t->points[2].x, t->points[2].y}, BLUE);
  }
}

void Visualisation::draw() const {
  BeginDrawing();
  if (redLight) {
    ClearBackground(RED);
  } else {
    ClearBackground(RAYWHITE);
  }
  drawTriangles();
  EndDrawing();
}

bool Visualisation::shouldExit() const { return WindowShouldClose(); }

void Visualisation::handleInput() {
  Vector2 mouse = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and !Carrying) {
    for (triangle *t : triangles) {
      if (isMouseInsideTriangle(*t, mouse)) {
        Carrying = t;
      }
    }
  }

  // Puszczenie
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    Carrying = nullptr;
  }

  // Jeśli niesiemy, aktualizujemy pozycję
  if (Carrying) {
    float offsetX = mouse.x - Carrying->points[0].x;
    float offsetY = mouse.y - Carrying->points[0].y;
    for (auto &p : Carrying->points) {
      p.x += offsetX;
      p.y += offsetY;
    }
  }
}

bool Visualisation::isMouseInsideTriangle(const triangle &t, Vector2 pt) {
  return CheckCollisionPointTriangle(Vector2{pt.x, pt.y},
                                     Vector2{t.points[0].x, t.points[0].y},
                                     Vector2{t.points[1].x, t.points[1].y},
                                     Vector2{t.points[2].x, t.points[2].y});
}
