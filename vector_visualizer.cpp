#include "vector_visualizer.hpp"
#include "global_variables.hpp"
#include "vector.hpp"
#include <cmath>
#include <raylib.h>
const double pi = global.pi;
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
  vector arrowEnd_1 = vector(cos(arrowAngle - global.arrow_tip_line_angle),
                             sin(arrowAngle - global.arrow_tip_line_angle)) *
                      global.arrow_tip_line_length;
  vector arrowEnd_2 = vector(cos(arrowAngle + global.arrow_tip_line_angle),
                             sin(arrowAngle + global.arrow_tip_line_angle)) *
                      global.arrow_tip_line_length;
  // we add origin and the vec (vec_local is the same) to these vectors bcz
  // reasons stated at the start of the func
  arrowEnd_1 = arrowEnd_1 + vec_local;
  arrowEnd_2 = arrowEnd_2 + vec_local;

  DrawLine(vec_local.x, vec_local.y, arrowEnd_1.x, arrowEnd_1.y, clr);
  DrawLine(vec_local.x, vec_local.y, arrowEnd_2.x, arrowEnd_2.y, clr);
  //
}
Image genGridImage_normal(int spacing) {
  vectorf win = global.win;
  vector origin = global.origin;
  Image img = GenImageColor(global.win.x, global.win.y, BLACK);

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
  return img;
}
void saveImage(Image img, std::string name) {
  ExportImage(img, name.c_str());
  UnloadImage(img);
}
Image genGridImage(int spacing, vector ihat_prime, vector jhat_prime) {

  vector win = vecfToVec(global.win);
  vector origin = global.origin;
  vector toDrawStart;
  vector toDrawEnd;
  Image img = GenImageColor(global.win.x, global.win.y, BLACK);

  toDrawStart =
      vector(origin.x, win.y).transform_return(ihat_prime, jhat_prime);
  toDrawEnd = vector(origin.x, 0).transform_return(ihat_prime, jhat_prime);
  ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                WHITE);
  toDrawStart =
      vector(win.x, origin.y).transform_return(ihat_prime, jhat_prime);
  toDrawEnd = vector(0, origin.y).transform_return(ihat_prime, jhat_prime);
  ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                WHITE);
  for (int i = 1; i < origin.x / spacing; i++) {
    toDrawStart = vector(origin.x + i * spacing, win.y)
                      .transform_return(ihat_prime, jhat_prime);
    toDrawEnd = vector(origin.x + i * spacing, 0)
                    .transform_return(ihat_prime, jhat_prime);
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
    toDrawStart = vector(origin.x - i * spacing, win.y)
                      .transform_return(ihat_prime, jhat_prime);
    toDrawEnd = vector(origin.x - i * spacing, 0)
                    .transform_return(ihat_prime, jhat_prime);
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
  }
  for (int i = 1; i < origin.y / spacing; i++) {
    toDrawStart = vector(win.x, origin.y + i * spacing)
                      .transform_return(ihat_prime, jhat_prime);
    toDrawEnd = vector(0, origin.y + i * spacing)
                    .transform_return(ihat_prime, jhat_prime);
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
    toDrawStart = vector(win.x, origin.y - i * spacing)
                      .transform_return(ihat_prime, jhat_prime);
    toDrawEnd = vector(0, origin.y - i * spacing)
                    .transform_return(ihat_prime, jhat_prime);
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
  }
  return img;
}
