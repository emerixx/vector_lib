#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "vector.hpp"

struct {
  const double pi = 3.14159265;
  const double arrow_tip_line_angle = pi / 6; // = 30 degrees
  const int arrow_tip_line_length = 30;
  const vectorf win = vectorf(1600, 900);
  const vector origin = vecfToVec(win) / 2;
} global;

#endif // GLOBAL_VARIABLES_H
