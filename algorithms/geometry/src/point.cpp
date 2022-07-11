#include "../point.h"
#include "../vector.h"
#include "../segment.h"

geometry::Point::Point() : x_(0), y_(0) {
}

geometry::Point::Point(const Point &other) : x_(other.x_), y_(other.y_) {
}

geometry::Point::Point(const int64_t a, const int64_t b) : x_(a), y_(b) {
}

bool geometry::Point::ContainsPoint(const Point &other) const {
  return (other.x_ == x_ && other.y_ == y_);
}

bool geometry::Point::CrossesSegment(const Segment &s) const {
  Vector v1(x_ - s.GetBeg().x_, y_ - s.GetBeg().y_);
  Vector v2(s.GetEnd().x_ - x_, s.GetEnd().y_ - y_);
  return (v1.Scal(v2) >= 0 && v1.VectMult(v2) == 0);
}

geometry::Point *geometry::Point::Clone() const {
  return new Point(x_, y_);
}

std::string geometry::Point::ToString() const {
  std::string ret = "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  return ret;
}

geometry::Point &geometry::Point::Move(const Vector &v) {
  x_ += v.GetI();
  y_ += v.GetJ();
  return *this;
}

int64_t geometry::Point::GetX() const {
  return x_;
}

int64_t geometry::Point::GetY() const {
  return y_;
}

bool geometry::Point::operator==(const geometry::Point &p) {
  return (x_ == p.GetX() && y_ == p.GetY());
}

geometry::Point &geometry::Point::operator+=(const geometry::Vector &v) {
  x_ += v.GetI();
  y_ += v.GetJ();
  return *this;
}

geometry::Vector geometry::Point::operator-(const geometry::Point &second) const {
  geometry::Vector other(second, *this);  //порядок тот?
  return other;
}