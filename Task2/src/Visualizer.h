#pragma once

#include <raylib.h>

#include <vector>

struct triangle;
struct vec2;

/**
 * Class responsible for visualization and interaction with triangles
 * Manages scene rendering, camera control and user interactions
 */
class Visualizer {
   public:
    /** Initializes visualization window with given dimensions */
    explicit Visualizer(int width, int height, int fps = 60);
    ~Visualizer();

    bool isColliding = false;

    /** Handles all user input (mouse, keyboard) */
    void handleInput();

    /** Renders the current scene */
    void draw() const;

    /** Adds a new triangle to the visualization */
    void addTriangle(triangle& triangle);

    /** Checks if the visualizer should close */
    [[nodiscard]] bool shouldClose() const;

   private:
    // Helper methods for interaction handling
    bool isMouseInsideTriangle(const triangle& triangle, Vector2 point) const;
    void handleCameraControl();
    void handleTriangleSelection(Vector2 mouseWorldPos);
    void handleTriangleTransformation(Vector2 mouseWorldPos);
    void drawAllTriangles() const;
    void drawCoordinateGrid() const;

    // Camera state
    Camera2D camera{.offset = {0, 0}, .target = {0, 0}, .rotation = 0.0f, .zoom = 1.0f};

    // Window dimensions
    int screenWidth;
    int screenHeight;

    // Triangle collection
    std::vector<triangle*> triangles;

    // Interaction state
    triangle* draggedTriangle = nullptr;
    triangle* selectedTriangle = nullptr;
    triangle* resizedTriangle = nullptr;
    vec2* selectedVertex = nullptr;
    Vector2 dragStartPosition;
};
