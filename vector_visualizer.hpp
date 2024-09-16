
#ifndef VECTOR_VISUALIZER_H
#define VECTOR_VISUALIZER_H

#include "global_variables.hpp"
#include "vector.hpp"
#include <raylib.h>

Image genGridImage_normal(int spacing);
Image genGridImage(int spacing, mml::vector2 ihat_prime,
                   mml::vector2 jhat_prime);
void draw_line_vec(mml::vector2 start, mml::vector2 end, Color clr);
void drawGrid(int spacing, mml::matrix transformation_matrix);
void drawGridImage(Image grid);
void drawVector(const mml::vector2 origin, mml::vector2 vec, const Color clr);
void saveImage(Image img, std::string name);
#endif // VECTOR_VISUALIZER_H
