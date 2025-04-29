#include "src/Application.h"
#include "src/Visualizer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
    // Create two triangles
    triangle t1{{{{530, 100}, {300, 450}, {750, 448}}}};
    triangle t2{{{{450, 100}, {50, 100}, {250, 450}}}};

    Visualizer vis(WINDOW_WIDTH, WINDOW_HEIGHT);
    vis.addTriangle(t1);
    vis.addTriangle(t2);

    while (!vis.shouldClose()) {
        vis.handleInput();

        // If the triangles collide, indicate it
        vis.isColliding = isColliding(t1, t2);

        vis.draw();
    }
}
