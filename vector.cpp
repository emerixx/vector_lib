#include "vector.hpp"
#include <cmath>

vector operator-(vector a, vector b) {
  return vector(a.x - b.x, a.y - b.y, a.z - b.z);
}
vector operator+(vector a, vector b) {
  return vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

vector operator/(vector a, double b) {

  return vector(a.x / b, a.y / b, a.z / b);
}
vector operator*(vector a, double b) {

  return vector(a.x * b, a.y * b, a.z * b);
}
vectorf vecToVecf(vector a) { return vectorf(a.x, a.y, a.z); }
vector vecfToVec(vectorf a) { return vector(a.x, a.y, a.z); }
double magnitude(vector a) {
  return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

vector normalize(vector a){
  return a/magnitude(a);
}
vector opposite(vector a){
  return vector(-a.x, -a.y, -a.z);
}
