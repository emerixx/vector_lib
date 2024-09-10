#include "vector.hpp"
#include <cmath>
#include <iostream>

vector2 operator-(vector2 a, vector2 b) {
  return vector2(a.x - b.x, a.y - b.y);
}
vector2 operator+(vector2 a, vector2 b) {
  return vector2(a.x + b.x, a.y + b.y);
}

vector2 operator/(vector2 a, double b) { return vector2(a.x / b, a.y / b); }
vector2 operator*(vector2 a, double b) { return vector2(a.x * b, a.y * b); }
vector2 operator*(vector2 a, vector2 b) {
  return vector2(a.x * b.x, a.y * b.y);
}

bool operator>(vector2 a, vector2 b) { return a.x > b.x && a.y > b.y; }
bool operator>=(vector2 a, vector2 b) { return a.x >= b.x && a.y >= b.y; }
bool operator<(vector2 a, vector2 b) { return a.x < b.x && a.y < b.y; }
bool operator<=(vector2 a, vector2 b) { return a.x <= b.x && a.y <= b.y; }

double vector2::mag() { return sqrt(pow(x, 2) + pow(y, 2)); }

vector2 vector2::unit() { return *this / mag(); }
vector2 vector2::opposite() { return vector2(-x, -y); }
vector2 vector2::transform_return(vector2 ihat_prime, vector2 jhat_prime) {
  return vector2(ihat_prime.x * x + jhat_prime.x * y,
                 ihat_prime.y * x + jhat_prime.y * y);
}
void vector2::transform(vector2 ihat_prime, vector2 jhat_prime) {
  double setx = ihat_prime.x * x + jhat_prime.x * y;
  y = ihat_prime.y * x + jhat_prime.y * y;
  x = setx;
}
vector2 vector2::abs() { return vector2(std::abs(x), std::abs(y)); };
void printvec(vector2 a) {
  std::cout << "vector: {" << a.x << ", " << a.y << "}\n";
}
void printvec(vector2 a, std::string name) {
  std::cout << name << ": {" << a.x << ", " << a.y << "}\n";
}
double sign(double a) { return a / std::abs(a); }
