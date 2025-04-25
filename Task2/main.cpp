#include "raylib.h"

int main() {

  {
    // Inicjalizacja okna
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib - podstawowe okno");

    // Ustawienie docelowej liczby klatek na sekundę
    SetTargetFPS(60);

    // Główna pętla gry
    while (!WindowShouldClose()) // Dopóki użytkownik nie zamknie okna
    {
      // Rozpoczęcie rysowania
      BeginDrawing();

      // Wyczyść tło na biało
      ClearBackground(RAYWHITE);

      // Narysuj tekst na ekranie
      DrawText("Witaj w raylib!", 190, 200, 20, LIGHTGRAY);

      // Zakończenie rysowania
      EndDrawing();
    }

    // Zamknięcie okna i zakończenie programu
    CloseWindow();

    return 0;
  }
}
