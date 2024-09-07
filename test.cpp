#include "vector.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
const double pi = 3.14159265;
const bool linearMode = false;
vectorf win = vectorf(1600, 900);
vector origin = vecfToVec(win) / 2;
int arrowLength = 30;
double arrowTipAngle = pi / 6; // = 30 deg
void genGrid();
void genGridTransformed(vector ihat_prime, vector jhat_prime);
void drawVector(vector origin, vector vec, Color clr);
int main() {
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
    vec.transform({2, 1.7}, {0.43, -2});
    drawVector(origin, vec, RED);
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void genGrid() {
  Image img = GenImageColor(win.x, win.y, BLACK);
  int spacing = 75;

  ImageDrawLine(&img, origin.x, win.y, origin.x, 0, WHITE);
  ImageDrawLine(&img, win.x, origin.y, 0, origin.y, WHITE);
  for (int i = 1; i < origin.x / spacing; i++) {
    ImageDrawLine(&img, origin.x + i * spacing, win.y, origin.x + i * spacing,
                  0, DARKGRAY);
    ImageDrawLine(&img, origin.x - i * spacing, win.y, origin.x - i * spacing,
                  0, DARKGRAY);
  }
  for (int i = 1; i < origin.y / spacing; i++) {
    ImageDrawLine(&img, win.x, origin.y + i * spacing, 0,
                  origin.y + i * spacing, DARKGRAY);
    ImageDrawLine(&img, win.x, origin.y - i * spacing, 0,
                  origin.y - i * spacing, DARKGRAY);
  }
  ExportImage(img, "grid.png");
  UnloadImage(img);
}
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
}
