
#ifndef VECTOR_VISUALIZER_H
#define VECTOR_VISUALIZER_H

#include "global_variables.hpp"
#include "vector.hpp"
#include <raylib.h>

Image genGridImage_normal(int spacing);
Image genGridImage(int spacing, vector ihat_prime, vector jhat_prime);
void drawGridImage(Image grid);
void drawVector(const vector origin, vector vec, const Color clr);
void saveImage(Image img, std::string name);
#endif // VECTOR_VISUALIZER_H
