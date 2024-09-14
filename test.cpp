#include "global_variables.hpp"
#include "vector.hpp"
#include "vector_visualizer.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
const double pi = global.pi;
mml::vector2 win = global.win;
mml::vector2 origin = global.origin;
int main() {
  mml::matrix matrix = mml::matrix({2, 2});
  matrix.print();
  matrix[0] = {0, 1};
  matrix[1] = {1, 0};
  matrix.print();
  std::cout << matrix.determinant() << "\n";
  return 0;
  // saveImage(genGridImage(15, {1, 0}, {0, 1}), "grid_test.png");
  InitWindow(win.x, win.y, "");
  SetTargetFPS(60);
  Image grid_img = genGridImage(45, {1, 0}, {0, 1});
  Texture2D grid = LoadTextureFromImage(grid_img);
  UnloadImage(grid_img);
  mml::vector2 vec;
  double i = 0;
  Color clrs[] = {WHITE, RED, BLUE, GREEN, VIOLET, LIGHTGRAY, YELLOW};
  while (!WindowShouldClose()) {
    if (i < 2 && 0) {
      i += 1.f / 600;
    }
    Vector2 mps = GetMousePosition();
    mml::vector2 mousepos = mml::vector2(mps.x, mps.y);
    vec = mml::vector2(mousepos.x, mousepos.y) - origin;
    vec.y *= -1;
    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexture(grid, 0, 0, WHITE);
    // drawGrid(60, {1, i}, {i, 1});

    drawVector(origin, vec, clrs[0]);
    drawVector(origin, vec.transform_return({0, 1}, {1, 0}), clrs[1]);

    vec.transform(matrix);
    drawVector(origin, vec * 0.99, clrs[2]);
    DrawFPS(0, 0);
    EndDrawing();
  }
  UnloadTexture(grid);
  CloseWindow();
  return 0;
}
