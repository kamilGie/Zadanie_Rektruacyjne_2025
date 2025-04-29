#include "Visualizer.h"

#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <limits>

#include "Application.h"

namespace {
// Stałe konfiguracyjne
constexpr int GRID_SPACING = 50;
constexpr Color GRID_COLOR = CLITERAL(Color){120, 120, 120, 200};
constexpr Color BACKGROUND_COLOR = CLITERAL(Color){60, 60, 60, 255};
constexpr Color HIGHLIGHT_COLOR = CLITERAL(Color){150, 255, 150, 100};
constexpr Color COLLISION_COLOR = CLITERAL(Color){90, 60, 60, 255};
constexpr Color TRIANGLE_COLOR = CLITERAL(Color){55, 150, 50, 255};
constexpr Color SELECTED_TRIANGLE_COLOR = CLITERAL(Color){135, 250, 130, 255};
constexpr float MIN_ZOOM = 0.1f;
constexpr float MAX_ZOOM = 5.0f;

constexpr float manhattanDistance(float x1, float y1, float x2, float y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

constexpr float calculateSignedArea(vec2 a, vec2 b, vec2 c) {
    return 0.5f * -((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}
}  // namespace

Visualizer::Visualizer(int width, int height, int fps) : screenWidth(width), screenHeight(height) {
    InitWindow(width, height, "Triangle Visualizer");
    SetTargetFPS(fps);
}

Visualizer::~Visualizer() { CloseWindow(); }

void Visualizer::addTriangle(triangle& triangle) { triangles.push_back(&triangle); }

void Visualizer::drawCoordinateGrid() const {
    const Vector2 worldTopLeft = GetScreenToWorld2D({0, 0}, camera);
    const Vector2 worldBottomRight =
        GetScreenToWorld2D({static_cast<float>(screenWidth), static_cast<float>(screenHeight)}, camera);

    // Calculate visible grid bounds
    const float startX = ceilf(worldTopLeft.x / GRID_SPACING) * GRID_SPACING;
    const float endX = floorf(worldBottomRight.x / GRID_SPACING) * GRID_SPACING;
    const float startY = ceilf(worldTopLeft.y / GRID_SPACING) * GRID_SPACING;
    const float endY = floorf(worldBottomRight.y / GRID_SPACING) * GRID_SPACING;

    // Draw horizontal grid lines
    for (float y = startY; y <= endY; y += GRID_SPACING) {
        DrawLineV({worldTopLeft.x, y}, {worldBottomRight.x, y}, GRID_COLOR);
    }

    // Draw vertical grid lines
    for (float x = startX; x <= endX; x += GRID_SPACING) {
        DrawLineV({x, worldTopLeft.y}, {x, worldBottomRight.y}, GRID_COLOR);
    }
}

void Visualizer::drawAllTriangles() const {
    // Currently manipulated triangle (being moved or resized)
    const triangle* activeTriangle = nullptr;

    for (const triangle* triangle : triangles) {
        const auto& points = triangle->points;
        const bool isActive = (triangle == selectedTriangle) && (resizedTriangle || draggedTriangle);

        if (!isActive) {
            DrawTriangle({points[0].x, points[0].y}, {points[1].x, points[1].y}, {points[2].x, points[2].y},
                         TRIANGLE_COLOR);
        } else {
            activeTriangle = triangle;
        }
    }

    if (selectedTriangle) {
        const auto& points = selectedTriangle->points;
        // Draw lines on last active triangle
        DrawTriangleLines({points[0].x, points[0].y}, {points[1].x, points[1].y}, {points[2].x, points[2].y},
                          HIGHLIGHT_COLOR);

        if (activeTriangle) {
            DrawTriangle({points[0].x, points[0].y}, {points[1].x, points[1].y}, {points[2].x, points[2].y},
                         SELECTED_TRIANGLE_COLOR);
        }
    }
}

void Visualizer::draw() const {
    BeginDrawing();
    ClearBackground(isColliding ? COLLISION_COLOR : BACKGROUND_COLOR);

    BeginMode2D(camera);
    drawCoordinateGrid();
    drawAllTriangles();
    EndMode2D();

    EndDrawing();
}

bool Visualizer::shouldClose() const { return WindowShouldClose(); }

void Visualizer::handleTriangleTransformation(Vector2 mouseWorldPos) {
    if (draggedTriangle) {
        const Vector2 delta = Vector2Subtract(mouseWorldPos, dragStartPosition);
        for (auto& vertex : draggedTriangle->points) {
            vertex.x += delta.x;
            vertex.y += delta.y;
        }
        dragStartPosition = mouseWorldPos;
    }

    // Zmiana rozmiaru trójkąta z walidacją pola
    if (resizedTriangle && selectedVertex) {
        const vec2 original = *selectedVertex;
        *selectedVertex = {mouseWorldPos.x, mouseWorldPos.y};

        const auto& p = resizedTriangle->points;
        if (calculateSignedArea(p[0], p[1], p[2]) < 1000.0f) {
            *selectedVertex = original;
        }
    }
}

void Visualizer::handleTriangleSelection(Vector2 mousePos) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float minDistance = std::numeric_limits<float>::max();

        for (triangle* triangle : triangles) {
            for (int i = 0; i < 3; ++i) {
                const float distance =
                    manhattanDistance(mousePos.x, mousePos.y, triangle->points[i].x, triangle->points[i].y);

                if (distance < (25.0f / camera.zoom) && distance < minDistance) {
                    minDistance = distance;
                    SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
                    selectedVertex = &triangle->points[i];
                    resizedTriangle = triangle;
                    selectedTriangle = triangle;
                    draggedTriangle = nullptr;
                }
            }

            // if we click inside triangle to grab not to resize
            if (!resizedTriangle && isMouseInsideTriangle(*triangle, mousePos)) {
                SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
                draggedTriangle = triangle;
                selectedTriangle = triangle;
                dragStartPosition = mousePos;
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        draggedTriangle = nullptr;
        resizedTriangle = nullptr;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void Visualizer::handleCameraControl() {
    // Camera moving
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
        const Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    // Zoom on scrool
    const float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        const Vector2 mouseBeforeZoom = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.zoom = std::clamp(camera.zoom + wheel * 0.1f, MIN_ZOOM, MAX_ZOOM);
        const Vector2 mouseAfterZoom = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.target = Vector2Add(camera.target, Vector2Subtract(mouseBeforeZoom, mouseAfterZoom));
    }
}

void Visualizer::handleInput() {
    const Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
    handleTriangleSelection(mouseWorldPos);
    handleTriangleTransformation(mouseWorldPos);
    handleCameraControl();
}

bool Visualizer::isMouseInsideTriangle(const triangle& triangle, Vector2 point) const {
    return CheckCollisionPointTriangle(point, {triangle.points[0].x, triangle.points[0].y},
                                       {triangle.points[1].x, triangle.points[1].y},
                                       {triangle.points[2].x, triangle.points[2].y});
}
