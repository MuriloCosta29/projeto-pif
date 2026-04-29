#include <raylib.h>

int main() {
  InitWindow(800, 600, "Stan James"); // Initialize window and OpenGL context

  while (!WindowShouldClose()) {
    BeginDrawing();            // Setup canvas (framebuffer) to start drawing
    ClearBackground(RAYWHITE); // Set background color (framebuffer clear color)
    DrawText("Stan James", 300, 280, 40,
             BLACK); // Draw text (using default font)
    EndDrawing();    // End canvas drawing and swap buffers (double buffering)
  }

  CloseWindow(); // Close window and unload OpenGL context
  return 0;
}
