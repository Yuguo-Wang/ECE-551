#include "circle.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double r1 = this->radius;
  double r2 = otherCircle.radius;

  if (r1 + r2 <= d) {
    return 0.0;
  }

  if (std::fabs(r1 - r2) >= d) {
    return M_PI * std::min(r1, r2) * std::min(r1, r2);
  }

  double angle1;
  double angle2;
  angle1 = 2.0 * acos((r1 * r1 - r2 * r2 + d * d) / (2.0 * r1 * d));
  angle2 = 2.0 * acos((r2 * r2 - r1 * r1 + d * d) / (2.0 * r2 * d));

  double res1, res2;
  res1 = 0.5 * r1 * r1 * (angle1 - sin(angle1));
  res2 = 0.5 * r2 * r2 * (angle2 - sin(angle2));
  return res1 + res2;
}
