#include "../point.h"
#include <cmath>
#include "../vector.h"

geometry::Vector::~Vector() = default;

geometry::Vector::Vector() : i_(0), j_(0) {
}

geometry::Vector::Vector(int64_t a, int64_t b) : i_(a), j_(b) {
}

int64_t geometry::Vector::GetI() const {
  return i_;
}

int64_t geometry::Vector::GetJ() const {
  return j_;
}

long double geometry::Vector::Lenght() const {
  return std::sqrt(i_ * i_ + j_ * j_);
}

int64_t geometry::Vector::Scal(geometry::Vector &b) const {
  return i_ * b.i_ + j_ * b.j_;
}

int64_t geometry::Vector::VectMult(geometry::Vector &b) const {
  return i_ * b.j_ - b.i_ * j_;
}

geometry::Vector::Vector(const geometry::Point &first, const geometry::Point &second)
    : i_(second.GetX() - first.GetX()), j_(second.GetY() - first.GetY()) {
}

std::string geometry::Vector::ToString() const {
  std::string ret = "Vector(" + std::to_string(i_) + ", " + std::to_string(j_) + ")";
  return ret;
}