#include "../include/game.h"
#include <raylib.h>

int main() {
  InitWindow(800, 600, "Stan James"); // Initialize window and OpenGL context

  Jogo jogo;
  inicializar_jogo(&jogo);

  while (!WindowShouldClose()) {
    atualizar_jogo(&jogo);
    BeginDrawing();            // Setup canvas (framebuffer) to start drawing
    ClearBackground(RAYWHITE); // Set background color (framebuffer clear color)
    DrawText("Stan James", 300, 220, 40,
             BLACK); // Draw text (using default font)
    if (jogo.estado_atual == MENU) {
      DrawText("Press SPACE to enter", 240, 300, 40, BLACK);
    }

    if (jogo.estado_atual == MIRANDO) {
      DrawText("MIRANDO", 320, 300, 40, BLACK);
    }
    EndDrawing(); // End canvas drawing and swap buffers (double buffering)
  }

  CloseWindow(); // Close window and unload OpenGL context
  return 0;
}
