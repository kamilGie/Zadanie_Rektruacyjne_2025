#include "src/Application.h"
#include "src/Visualisation.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
    // tworze 2 trojkaty
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{400, 150}, {301, 351}, {500, 350}}}};

    Visualisation vis(WINDOW_WIDTH, WINDOW_HEIGHT);
    vis.addTriangle(t1);
    vis.addTriangle(t2);

    while (!vis.shouldExit()) {
        vis.handleInput();

        // Jesli trojkaty koliduja informuje
        vis.redLight = isColliding(t1, t2);

        vis.draw();
    }
}
