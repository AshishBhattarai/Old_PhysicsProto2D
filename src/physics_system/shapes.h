#pragma once

namespace physics {

struct Shape {
  virtual ~Shape() {}
};

struct Circle : Shape {
  float radius;

  Circle(float radius) : radius(radius) {}
};
} // namespace physics
