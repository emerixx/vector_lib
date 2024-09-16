#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "vector.hpp"

struct {
  const double pi = 3.14159265;
  const double arrow_tip_line_angle = pi / 6; // = 30 degrees
  const int arrow_tip_line_length = 30;
  const mml::vector2 win = mml::vector2(16 * 70, 9 * 70);
  const mml::vector2 origin = win / 2;

} global;

#endif // GLOBAL_VARIABLES_H
