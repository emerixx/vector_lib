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
  mml::matrix mtrx = mml::matrix({2, 2});
  mml::matrix normal_matrix = mml::matrix({2, 2});
  normal_matrix[0] = {1, 0};
  normal_matrix[1] = {0, 1};
  // saveImage(genGridImage(15, {1, 0}, {0,,, 1}), "grid_test.png");
  SetTraceLogLevel(LOG_WARNING);
  InitWindow(win.x, win.y, "");
  SetTargetFPS(60);
  Image grid_img = genGridImage(45, {1, 0}, {0, 1});
  Texture2D grid = LoadTextureFromImage(grid_img);
  UnloadImage(grid_img);
  mml::vector2 vec;
  double theta = 0;
  Color clrs[] = {WHITE, RED, BLUE, GREEN, VIOLET, LIGHTGRAY, YELLOW};
  while (!WindowShouldClose()) {
    if (theta < 2 * pi) {
      theta += 1.f / 600;
      // mtrx[0] = {cos(theta), -sin(theta)};
      mtrx[0] = {1, theta};
      // mtrx[1] = {sin(theta), cos(theta)};
      mtrx[1] = {theta, 1};
    } else {
      theta = 0;
    }
    Vector2 mps = GetMousePosition();
    mml::vector2 mousepos = mml::vector2(mps.x, mps.y);
    vec = mml::vector2(mousepos.x, mousepos.y) - origin;
    vec.y *= -1;
    vec.transform(mtrx);
    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexture(grid, 0, 0, WHITE);
    drawGrid(10, mtrx);
    // drawVector(origin, vec, clrs[0]);
    //  drawGrid(60, normal_matrix);

    DrawFPS(0, 0);
    EndDrawing();
  }
  UnloadTexture(grid);
  CloseWindow();
  return 0;
}
