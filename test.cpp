#include "global_variables.hpp"
#include "vector.hpp"
#include "vector_visualizer.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
const double pi = global.pi;
vector2 win = global.win;
vector2 origin = global.origin;
int main() {

  saveImage(genGridImage(15, {1, 0}, {0, 1}), "grid_test.png");
  // return 0;
  InitWindow(win.x, win.y, "");
  SetTargetFPS(60);
  Image grid_img = genGridImage(45, {1, 0}, {0, 1});
  Texture2D grid = LoadTextureFromImage(grid_img);
  UnloadImage(grid_img);
  vector2 vec;
  double i = 0;
  Color clrs[] = {WHITE, RED, BLUE, GREEN, VIOLET, LIGHTGRAY, YELLOW};
  while (!WindowShouldClose()) {
    if (i < 2) {
      i += 1.f / 600;
    }
    Vector2 mousepos = GetMousePosition();
    vec = vector2(mousepos.x, mousepos.y) - origin;
    vec.y *= -1;
    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexture(grid, 0, 0, WHITE);
    drawGrid(60, {1, i}, {i, 1});

    drawVector(origin, vec, clrs[0]);
    vec.transform({0, 1}, {1, 0});
    drawVector(origin, vec, clrs[1]);
    vec.transform({0, 1}, {1, 0});
    drawVector(origin, vec * 0.95, clrs[2]);
    DrawFPS(0, 0);
    EndDrawing();
  }
  UnloadTexture(grid);
  CloseWindow();
  return 0;
}
