#ifndef VECTOR_H
#define VECTOR_H

#include <string>
class vector {
public:
  double x;
  double y;
  double z;
  vector(double x_in, double y_in) : x(x_in), y(y_in), z(0) {}
  vector(double x_in, double y_in, double z_in) : x(x_in), y(y_in), z(z_in) {}
  vector() : x(0), y(0), z(0) {}
  vector unit();
  double mag();
  vector opposite();
  void transform(vector ihat_prime, vector jhat_prime);
  vector transform_return(vector ihat_prime, vector jhat_prime);
  vector abs();
  vector set_z_temp(double a);
};

struct vectorf {
  float x;
  float y;
  float z;
  vectorf(float x_in, float y_in) : x(x_in), y(y_in), z(0) {}
  vectorf(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {}
  vectorf() : x(0), y(0), z(0) {}
};
class vector2 {
public:
  double x;
  double y;
  vector2(double x_in, double y_in) : x(x_in), y(y_in) {}
  vector2() : x(0), y(0) {}
  vector2 unit();
  double mag();
  vector2 opposite();
  void transform(vector ihat_prime, vector jhat_prime);
  vector2 transform_return(vector ihat_prime, vector jhat_prime);
  vector2 abs();
};

vector operator-(vector a, vector b);
vector operator+(vector a, vector b);
vector operator/(vector a, double b);
vector operator*(vector a, double b);
vector operator*(vector a, vector b);
bool operator>(vector a, vector b);
bool operator>=(vector a, vector b);
bool operator<(vector a, vector b);
bool operator<=(vector a, vector b);
vectorf vecToVecf(vector a);
vector vecfToVec(vectorf a);
void printvec(vector a);
void printvec(vector a, std::string name);
double sign(double a);

#endif // VECTOR_H
