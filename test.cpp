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

/*
void drawVector(const vector origin, vector vec, const Color clr) {
  vector vec_local = vec;
  // multiply by -1 since y+ is down
  vec_local.y *= -1;
  // add origin to vec since, (0, 0) is left top corner
  vec_local = vec_local + origin;
  // turn it 180 deg for some reason
  double arrowAngle = pi - atan(vec.y / vec.x);
  DrawLine(origin.x, origin.y, vec_local.x, vec_local.y, clr);

  //  compute arrow ends
  //  these 2 vectors would be correct if
  //  1. I add origin to them (which i do later)
  //  2. The vector im drawing is {0, n} where n∈ R and n > 0, follow up 2
  //  lines down
  if (vec.x < 0) {
    arrowAngle += pi;
  }
  vector arrowEnd_1 =
      vector(cos(arrowAngle - arrowTipAngle), sin(arrowAngle - arrowTipAngle)) *
      arrowLength;
  vector arrowEnd_2 =
      vector(cos(arrowAngle + arrowTipAngle), sin(arrowAngle + arrowTipAngle)) *
      arrowLength;
  // we add origin and the vec (vec_local is the same) to these vectors bcz
  // reasons stated at the start of the func
  arrowEnd_1 = arrowEnd_1 + vec_local;
  arrowEnd_2 = arrowEnd_2 + vec_local;

  DrawLine(vec_local.x, vec_local.y, arrowEnd_1.x, arrowEnd_1.y, clr);
  DrawLine(vec_local.x, vec_local.y, arrowEnd_2.x, arrowEnd_2.y, clr);
  //
}*/
