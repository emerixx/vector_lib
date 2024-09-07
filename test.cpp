#include "global_variables.hpp"
#include "vector.hpp"
#include "vector_visualizer.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
const double pi = global.pi;
vectorf win = global.win;
vector origin = global.origin;
int main() {
  saveImage(genGridImage(15, {1, 1}, {0, 1}), "grid_test.png");
  return 0;
  InitWindow(win.x, win.y, "");
  SetTargetFPS(60);
  Image grid_img = LoadImage("grid.png");
  Texture2D grid = LoadTextureFromImage(grid_img);
  UnloadImage(grid_img);
  vector vec;
  while (!WindowShouldClose()) {
    Vector2 mousepos = GetMousePosition();
    vec = vector(mousepos.x, mousepos.y) - origin;
    vec.y *= -1;
    BeginDrawing();

    DrawTexture(grid, 0, 0, WHITE);
    ClearBackground(BLACK);
    drawVector(origin, vec, WHITE);
    vec.transform({1, 1}, {0, 1});
    drawVector(origin, vec, RED);
    DrawFPS(0, 0);
    EndDrawing();
  }
  UnloadTexture(grid);
  CloseWindow();
  return 0;
}
