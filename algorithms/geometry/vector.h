#pragma once
#include "IShape.h"
#include <memory>
#include <cstring>

class geometry::Vector {
  int64_t i_;
  int64_t j_;

 public:
  ~Vector();
  Vector();
  Vector(const Point&, const Point&);
  Vector(int64_t a, int64_t b);
  int64_t GetI() const;
  int64_t GetJ() const;
  long double Lenght() const;
  int64_t Scal(Vector& b) const;
  int64_t VectMult(Vector& b) const;
  std::string ToString() const;
  Vector& operator=(const Vector&) = default;
};
