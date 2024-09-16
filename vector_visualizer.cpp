#include "vector_visualizer.hpp"
#include "global_variables.hpp"
#include "vector.hpp"
#include <cmath>
#include <iostream>
#include <raylib.h>
// umm, iirc i use pi somewhere, so i just assign it from globa.pi to pi so its
// less code

const double pi = global.pi;

void draw_line_vec(mml::vector2 start, mml::vector2 end, Color clr) {
  // this fuction draws a line from one point to another onto current renderer,
  // (0, 0) = middle of screen, y+ = up, x+ = right
  mml::vector2 origin = global.origin;
  // transforming by {1, 0}, {0, -1} just does vec.y=-vec.y
  // add origin since raylib uwu
  mml::vector2 start_loc = start.transform_return({1, 0}, {0, -1}) + origin;
  mml::vector2 end_loc = end.transform_return({1, 0}, {0, -1}) + origin;
  DrawLine(start_loc.x, start_loc.y, end_loc.x, end_loc.y, clr);
}
void img_draw_line_vec(Image *dst, mml::vector2 start, mml::vector2 end,
                       Color clr) {
  // this fuction draws a line from one point to another onto an img
  // (0, 0) = middle of screen, y+ = up, x+ = right
  mml::vector2 origin = global.origin;
  // transforming by {1, 0}, {0, -1} just does vec.y=-vec.y
  // add origin since raylib uwu
  mml::vector2 start_loc = start.transform_return({1, 0}, {0, -1}) + origin;
  mml::vector2 end_loc = end.transform_return({1, 0}, {0, -1}) + origin;
  ImageDrawLine(dst, start_loc.x, start_loc.y, end_loc.x, end_loc.y, clr);
}
void drawVector(const mml::vector2 origin, mml::vector2 vec, const Color clr) {
  mml::vector2 vec_local = vec;
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
  mml::vector2 arrowEnd_1 =
      mml::vector2(cos(arrowAngle - global.arrow_tip_line_angle),
                   sin(arrowAngle - global.arrow_tip_line_angle)) *
      global.arrow_tip_line_length;
  mml::vector2 arrowEnd_2 =
      mml::vector2(cos(arrowAngle + global.arrow_tip_line_angle),
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

// TODO
// TODO
// fix pls
void drawGrid(int spacing, mml::matrix transformation_matrix) {

  mml::vector2 win = global.win / 2;
  mml::vector2 origin = global.origin;
  double done = 0;
  mml::vector2 toDrawStart;
  mml::vector2 toDrawEnd;

  mml::matrix normal_matrix = mml::matrix({2, 2});
  normal_matrix[0] = {1, 0};
  normal_matrix[1] = {0, 1};
  mml::vector2 normal_ihat, normal_jhat;
  normal_ihat = {normal_matrix[0, 0], normal_matrix[1, 0]};
  normal_jhat = {normal_matrix[0, 1], normal_matrix[1, 1]};
  // transform each corner (non transformed) by inverse matrix of ihat_prime and
  mml::matrix inverse_transformation_matrix = transformation_matrix.inverse();
  mml::vector2 corner_grid_top_left = mml::vector2(-win.x / 2, -win.y / 2);
  mml::vector2 corner_grid_top_right = mml::vector2(win.x / 2, -win.y / 2);

  mml::vector2 corner_grid_bottom_left = mml::vector2(-win.x / 2, win.y / 2);

  mml::vector2 corner_grid_bottom_right = mml::vector2(win.x / 2, win.y / 2);

  mml::vector2 corner_grid_top_left_trans =
      corner_grid_top_left.transform_return(transformation_matrix);
  mml::vector2 corner_grid_top_right_trans =
      corner_grid_top_right.transform_return(transformation_matrix);

  mml::vector2 corner_grid_bottom_left_trans =
      corner_grid_bottom_left.transform_return(transformation_matrix);

  mml::vector2 corner_grid_bottom_right_trans =
      corner_grid_bottom_right.transform_return(transformation_matrix);
  // vector <= vector check if all values are <= (x,y and z)
  draw_line_vec(corner_grid_top_left, corner_grid_top_right, GRAY);
  draw_line_vec(corner_grid_top_right, corner_grid_bottom_right, GRAY);
  draw_line_vec(corner_grid_bottom_right, corner_grid_bottom_left, GRAY);
  draw_line_vec(corner_grid_bottom_left, corner_grid_top_left, GRAY);

  draw_line_vec(corner_grid_top_right, corner_grid_bottom_left, ORANGE);
  draw_line_vec(corner_grid_top_left, corner_grid_bottom_right, ORANGE);

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
  // create a method like matrix.basisVectors.ihat, .jhat please :sob:
  mml::matrix temp_trans_matrix = transformation_matrix;
  temp_trans_matrix[0, 0] = 1;
  temp_trans_matrix[1, 0] = 0;
  mml::matrix inverse_transformation_matrix_ihat_prime = mml::matrix({2, 2});
  inverse_transformation_matrix_ihat_prime = temp_trans_matrix.inverse();
  temp_trans_matrix = transformation_matrix;
  temp_trans_matrix[0, 1] = 0;
  temp_trans_matrix[1, 1] = 1;

  mml::matrix inverse_transformation_matrix_jhat_prime = mml::matrix({2, 2});
  inverse_transformation_matrix_jhat_prime = temp_trans_matrix.inverse();
  if (transformation_matrix[0, 1] < 0)
    transformation_matrix.invert();
  mml::vector2 ihat_prime = {transformation_matrix[0, 0],
                             transformation_matrix[1, 0]};
  mml::vector2 jhat_prime = {transformation_matrix[0, 1],
                             transformation_matrix[1, 1]};

  for (int i = 0; i < corner_grid_top_right_trans.mag() / spacing; i++) {
    done = i / (corner_grid_top_right_trans.mag() / spacing);
    // check what point will be at corner_grid_bottom_left after transformation
    // and transform that point
    // create a function to create a 2x2 matrix from jhat and ihat late TODO

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
  for (int i = 0; i < std::abs(corner_grid_top_right.y) / spacing; i++) {
    done = i / (std::abs(corner_grid_top_right.y) / spacing);
    toDrawStart =
        corner_grid_top_left.transform_return(ihat_prime, jhat_prime * done);
    toDrawEnd =
        corner_grid_top_right.transform_return(ihat_prime, jhat_prime * done);

    draw_line_vec(toDrawStart, toDrawEnd, PURPLE);
    toDrawStart =
        corner_grid_bottom_left.transform_return(ihat_prime, jhat_prime * done);
    toDrawEnd = corner_grid_bottom_right.transform_return(ihat_prime,
                                                          jhat_prime * done);
    draw_line_vec(toDrawStart, toDrawEnd, PURPLE);
  }
}

// here just for checking if stuff is transforming right, delete it later
// TODO
void drawGridOLD(int spacing, mml::matrix transformation_matrix) {

  mml::vector2 win = global.win / 1.2;
  mml::vector2 origin = global.origin;
  double done = 0;
  mml::vector2 toDrawStart;
  mml::vector2 toDrawEnd;
  mml::vector2 ihat_prime = {transformation_matrix[0, 0],
                             transformation_matrix[1, 0]};
  mml::vector2 jhat_prime = {transformation_matrix[0, 1],
                             transformation_matrix[1, 1]};
  // transform each corner (non transformed) by inverse matrix of ihat_prime and
  mml::matrix inverse_transformation_matrix = transformation_matrix.inverse();
  mml::vector2 corner_grid_top_left = mml::vector2(-win.x / 2, -win.y / 2);
  mml::vector2 corner_grid_top_right = mml::vector2(win.x / 2, -win.y / 2);

  mml::vector2 corner_grid_bottom_left = mml::vector2(-win.x / 2, win.y / 2);

  mml::vector2 corner_grid_bottom_right = mml::vector2(win.x / 2, win.y / 2);

  mml::vector2 corner_grid_top_left_trans = corner_grid_top_left;
  mml::vector2 corner_grid_top_right_trans = corner_grid_top_right;

  mml::vector2 corner_grid_bottom_left_trans = corner_grid_bottom_left;

  mml::vector2 corner_grid_bottom_right_trans = corner_grid_bottom_right;
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
  // create a method like matrix.basisVectors.ihat, .jhat please :sob:

  mml::matrix inverse_transformation_matrix_ihat_prime = mml::matrix({2, 2});
  inverse_transformation_matrix_ihat_prime = inverse_transformation_matrix;
  inverse_transformation_matrix_ihat_prime[0, 0] = 1;
  inverse_transformation_matrix_ihat_prime[1, 0] = 0;
  mml::matrix inverse_transformation_matrix_jhat_prime = mml::matrix({2, 2});
  inverse_transformation_matrix_jhat_prime = inverse_transformation_matrix;
  inverse_transformation_matrix_jhat_prime[0, 1] = 0;
  inverse_transformation_matrix_jhat_prime[1, 1] = 1;

  for (int i = 0; i < corner_grid_top_right_trans.x / spacing; i++) {
    done = i / (corner_grid_top_right_trans.x / spacing);
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

    draw_line_vec(toDrawStart, toDrawEnd, PURPLE);
    toDrawStart =
        corner_grid_bottom_left.transform_return(ihat_prime, jhat_prime * done);
    toDrawEnd = corner_grid_bottom_right.transform_return(ihat_prime,
                                                          jhat_prime * done);
    draw_line_vec(toDrawStart, toDrawEnd, PURPLE);
  }
}

// dont use these rn, i havent checked if they work in an eternity uwu
// TODO
Image genGridImage_normal(int spacing) {
  mml::vector2 win = global.win;
  mml::vector2 origin = global.origin;
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
Image genGridImage(int spacing, mml::vector2 ihat_prime,
                   mml::vector2 jhat_prime) {

  mml::vector2 win = global.win;
  mml::vector2 origin = global.origin;
  mml::vector2 toDrawStart;
  mml::vector2 toDrawEnd;
  Image img = GenImageColor(global.win.x, global.win.y, BLACK);
  mml::vector2 corner_top_left =
      mml::vector2(0, 0).transform_return(ihat_prime, jhat_prime);
  mml::vector2 corner_top_right =
      mml::vector2(win.x, 0).transform_return(ihat_prime, jhat_prime);

  mml::vector2 corner_bottom_left =
      mml::vector2(0, win.y).transform_return(ihat_prime, jhat_prime);

  mml::vector2 corner_bottom_right =
      mml::vector2(win.x, win.y).transform_return(ihat_prime, jhat_prime);
  /*
    img_draw_line_vec(&img, corner_top_left, corner_top_right, WHITE);
    img_draw_line_vec(&img, corner_top_right, corner_bottom_right, WHITE);
    img_draw_line_vec(&img, corner_bottom_right, corner_bottom_left, WHITE);
    img_draw_line_vec(&img, corner_bottom_left, corner_top_left, WHITE);

    img_draw_line_vec(&img, corner_top_right, corner_bottom_left, RED);
    img_draw_line_vec(&img, corner_top_left, corner_bottom_right, RED);
    return img;
    */
  toDrawStart = mml::vector2(0, win.y - origin.y)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
  toDrawEnd =
      mml::vector2(0, -origin.y).transform_return(ihat_prime, jhat_prime) +
      origin;
  ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                WHITE);
  toDrawStart = mml::vector2(win.x - origin.x, 0)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
  toDrawEnd =
      mml::vector2(-origin.x, 0).transform_return(ihat_prime, jhat_prime) +
      origin;
  ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                WHITE);
  for (int i = 1; i < origin.x / spacing; i++) {
    toDrawStart = mml::vector2(i * spacing, win.y - origin.y)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = mml::vector2(i * spacing, -origin.y)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
    toDrawStart = mml::vector2(-i * spacing, win.y - origin.y)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = mml::vector2(-i * spacing, -origin.y)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
  }

  for (int i = 1; i < origin.y / spacing; i++) {
    toDrawStart = mml::vector2(win.x - origin.x, i * spacing)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = mml::vector2(-origin.x, i * spacing)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
    toDrawStart = mml::vector2(win.x - origin.x, -i * spacing)
                      .transform_return(ihat_prime, jhat_prime) +
                  origin;
    toDrawEnd = mml::vector2(-origin.x, -i * spacing)
                    .transform_return(ihat_prime, jhat_prime) +
                origin;
    ImageDrawLine(&img, toDrawStart.x, toDrawStart.y, toDrawEnd.x, toDrawEnd.y,
                  DARKGRAY);
  }
  return img;
}
void saveImage(Image img, std::string name) {
  ExportImage(img, name.c_str());
  UnloadImage(img);
}
