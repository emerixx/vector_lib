
#ifndef VECTOR_VISUALIZER_H
#define VECTOR_VISUALIZER_H

#include "global_variables.hpp"
#include "vector.hpp"
#include <raylib.h>

Image genGridImage_normal(int spacing);
Image genGridImage(int spacing, vector2 ihat_prime, vector2 jhat_prime);
void draw_line_vec(vector2 start, vector2 end, Color clr);
void drawGrid(int spacing, vector2 ihat_prime, vector2 jhat_prime);
void drawGridImage(Image grid);
void drawVector(const vector2 origin, vector2 vec, const Color clr);
void saveImage(Image img, std::string name);
#endif // VECTOR_VISUALIZER_H
