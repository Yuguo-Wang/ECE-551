#include "point.hpp"

#include "math.h"

void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}

double Point::distanceFrom(const Point & p) {
  double res = sqrt(((x - p.x) * (x - p.x)) + (y - p.y) * (y - p.y));
  return res;
}
