#include "vector_visualizer.hpp"
#include "global_variables.hpp"
#include "vector.hpp"
#include <cmath>
#include <raylib.h>
// umm, iirc i use pi somewhere, so i just assign it from globa.pi to pi so its
// less code
const double pi = global.pi;

void draw_line_vec(vector start, vector end, Color clr) {
  // this fuctiion draws a line from one point to another onto current renderer,
  // (0, 0) = middle of screen, y+ = up, x+ = right
  vector origin = global.origin;
  // transforming by {1, 0}, {0, -1} just does vec.y=-vec.y
  // add origin since raylib uwu
  vector start_loc = start.transform_return({1, 0}, {0, -1}) + origin;
  vector end_loc = end.transform_return({1, 0}, {0, -1}) + origin;
  DrawLine(start_loc.x, start_loc.y, end_loc.x, end_loc.y, clr);
}
void img_draw_line_vec(Image *dst, vector start, vector end, Color clr) {
  // this fuctiion draws a line from one point to another onto an img
  // (0, 0) = middle of screen, y+ = up, x+ = right
  vector origin = global.origin;
  // transforming by {1, 0}, {0, -1} just does vec.y=-vec.y
  // add origin since raylib uwu
  vector start_loc = start.transform_return({1, 0}, {0, -1}) + origin;
  vector end_loc = end.transform_return({1, 0}, {0, -1}) + origin;
  ImageDrawLine(dst, start_loc.x, start_loc.y, end_loc.x, end_loc.y, clr);
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
void drawGrid(int spacing, vector ihat_prime, vector jhat_prime) {

  vector win = vecfToVec(global.win) / 2;
  vector origin = global.origin;
  double done = 0;
  vector toDrawStart;
  vector toDrawEnd;

  // transform each corner (non transformed) by inverse matrix of ihat_prime and
  // det(A) = ad-bc
  double determinant =
      ihat_prime.x * jhat_prime.y - ihat_prime.y * jhat_prime.x;
  // 1/(ad-bc) *
  // vector inverse_ihat_prime = 1 / ()

  vector corner_grid_top_left = vector(-win.x / 2, -win.y / 2);
  vector corner_grid_top_right = vector(win.x / 2, -win.y / 2);

  vector corner_grid_bottom_left = vector(-win.x / 2, win.y / 2);

  vector corner_grid_bottom_right = vector(win.x / 2, win.y / 2);

  vector corner_grid_top_left_trans =
      corner_grid_top_left.transform_return(ihat_prime, jhat_prime);
  vector corner_grid_top_right_trans =
      corner_grid_top_right.transform_return(ihat_prime, jhat_prime);

  vector corner_grid_bottom_left_trans =
      corner_grid_bottom_left.transform_return(ihat_prime, jhat_prime);

  vector corner_grid_bottom_right_trans =
      corner_grid_bottom_right.transform_return(ihat_prime, jhat_prime);
  // vector <= vector check if all values are <= (x,y and z)

  draw_line_vec(corner_grid_top_left_trans, corner_grid_top_right_trans, WHITE);
  draw_line_vec(corner_grid_top_right_trans, corner_grid_bottom_right_trans,
                WHITE);
  draw_line_vec(corner_grid_bottom_right_trans, corner_grid_bottom_left_trans,
                WHITE);
  draw_line_vec(corner_grid_bottom_left_trans, corner_grid_top_left_trans,
                WHITE);

  draw_line_vec(corner_grid_top_right_trans, corner_grid_bottom_left_trans,
                RED);
  draw_line_vec(corner_grid_top_left_trans, corner_grid_bottom_right_trans,
                RED);
  for (int i = 0; i < origin.x / spacing; i++) {
    done = i / (origin.x / spacing);

    toDrawStart =
        corner_grid_bottom_left.transform_return(ihat_prime * done, jhat_prime);
    toDrawEnd =
        corner_grid_top_left.transform_return(ihat_prime * done, jhat_prime);

    draw_line_vec(toDrawStart, toDrawEnd, GREEN);
    toDrawStart = corner_grid_bottom_right.transform_return(ihat_prime * done,
                                                            jhat_prime);
    toDrawEnd =
        corner_grid_top_right.transform_return(ihat_prime * done, jhat_prime);
    draw_line_vec(toDrawStart, toDrawEnd, GREEN);
  }
  for (int i = 0; i < origin.y / spacing; i++) {
    done = i / (origin.y / spacing);
    toDrawStart =
        corner_grid_top_left.transform_return(ihat_prime, jhat_prime * done);
    toDrawEnd =
        corner_grid_top_right.transform_return(ihat_prime, jhat_prime * done);

    draw_line_vec(toDrawStart, toDrawEnd, GREEN);
    toDrawStart =
        corner_grid_bottom_left.transform_return(ihat_prime, jhat_prime * done);
    toDrawEnd = corner_grid_bottom_right.transform_return(ihat_prime,
                                                          jhat_prime * done);
    draw_line_vec(toDrawStart, toDrawEnd, GREEN);
  }
}
Image genGridImage(int spacing, vector ihat_prime, vector jhat_prime) {

  vector win = vecfToVec(global.win);
  vector origin = global.origin;
  vector toDrawStart;
  vector toDrawEnd;
  Image img = GenImageColor(global.win.x, global.win.y, BLACK);
  vector corner_top_left =
      vector(0, 0).transform_return(ihat_prime, jhat_prime);
  vector corner_top_right =
      vector(win.x, 0).transform_return(ihat_prime, jhat_prime);

  vector corner_bottom_left =
      vector(0, win.y).transform_return(ihat_prime, jhat_prime);

  vector corner_bottom_right =
      vector(win.x, win.y).transform_return(ihat_prime, jhat_prime);
  /*
    img_draw_line_vec(&img, corner_top_left, corner_top_right, WHITE);
    img_draw_line_vec(&img, corner_top_right, corner_bottom_right, WHITE);
    img_draw_line_vec(&img, corner_bottom_right, corner_bottom_left, WHITE);
    img_draw_line_vec(&img, corner_bottom_left, corner_top_left, WHITE);

    img_draw_line_vec(&img, corner_top_right, corner_bottom_left, RED);
    img_draw_line_vec(&img, corner_top_left, corner_bottom_right, RED);
    return img;
    */
  toDrawStart =
      vector(0, win.y - origin.y).transform_return(ihat_prime, jhat_prime) +
      origin;
  toDrawEnd =
      vector(0, -origin.y).transform_return(ihat_prime, jhat_prime) + origin;
  ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                WHITE);
  toDrawStart =
      vector(win.x - origin.x, 0).transform_return(ihat_prime, jhat_prime) +
      origin;
  toDrawEnd =
      vector(-origin.x, 0).transform_return(ihat_prime, jhat_prime) + origin;
  ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                WHITE);
  for (int i = 1; i < origin.x / spacing; i++) {
    toDrawStart = vector(i * spacing, win.y - origin.y)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = vector(i * spacing, -origin.y)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
    toDrawStart = vector(-i * spacing, win.y - origin.y)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = vector(-i * spacing, -origin.y)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
  }

  for (int i = 1; i < origin.y / spacing; i++) {
    toDrawStart = vector(win.x - origin.x, i * spacing)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = vector(-origin.x, i * spacing)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
    toDrawStart = vector(win.x - origin.x, -i * spacing)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = vector(-origin.x, -i * spacing)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
  }
  return img;
}
