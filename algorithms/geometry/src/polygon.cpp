#include "../point.h"
#include "../vector.h"
#include "../polygon.h"
#include "../segment.h"
#include "../ray.h"

geometry::Polygon::Polygon(std::vector<Point> p) : points_(p) {
}

geometry::Polygon &geometry::Polygon::Move(const geometry::Vector &v) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i] += v;
  }
  return *this;
}

geometry::Polygon *geometry::Polygon::Clone() const {
  return new Polygon(points_);
}

bool geometry::Polygon::ContainsPoint(const geometry::Point &p) const {
  Ray r{p, Vector(9999, p.GetY() + 1)};
  int cnt = 0;
  cnt += r.CrossesSegment(Segment(points_[0], points_[points_.size() - 1]));
  if (Segment(points_[0], points_[points_.size() - 1]).ContainsPoint(p)) {
    return true;
  }
  for (size_t i = 0; i < points_.size() - 1; i++) {
    if (Segment(points_[i], points_[i + 1]).ContainsPoint(p)) {
      return true;
    }
    cnt += r.CrossesSegment(Segment(points_[i], points_[i + 1]));
  }
  return cnt % 2 == 1;
}

bool geometry::Polygon::CrossesSegment(const geometry::Segment &s) const {
  if (s.CrossesSegment({points_[points_.size() - 1], points_[0]})) {
    return true;
  }
  for (size_t i = 0; i < points_.size() - 1; i++) {
    if (s.CrossesSegment({points_[i], points_[i + 1]})) {
      return true;
    }
  }
  return false;
}

std::string geometry::Polygon::ToString() const {
  std::string ret = "Polygon(";
  for (size_t i = 0; i < points_.size() - 1; i++) {
    ret += points_[i].ToString();
    ret += ", ";
  }
  ret += points_[points_.size() - 1].ToString() + ")";
  return ret;
}