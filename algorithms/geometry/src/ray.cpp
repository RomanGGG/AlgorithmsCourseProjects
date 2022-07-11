#include "../point.h"
#include "../vector.h"
#include "../ray.h"
#include "../line.h"
#include "../segment.h"

geometry::Ray::~Ray() = default;

geometry::Ray::Ray() : begin_(0, 0), dir_({0, 0}) {
}

geometry::Ray::Ray(const geometry::Point &p1, const geometry::Point &p2) : begin_(p1), dir_(p1, p2) {
}

geometry::Ray::Ray(const geometry::Point &p, const geometry::Vector &v) : begin_(p), dir_(v) {
}

geometry::Ray::Ray(const geometry::Ray &ray) : begin_(ray.begin_), dir_(ray.dir_) {
}

//  geometry::Ray &geometry::Ray::operator=(const geometry::Ray &ray) {
//  begin_ = ray.GetBegin();
//  dir_ = ray.GetDirection();
//  return *this;
//  }

geometry::Ray &geometry::Ray::Move(const geometry::Vector &v) {
  begin_ += v;
  return *this;
}

bool geometry::Ray::ContainsPoint(const geometry::Point &p) const {
  Vector v1(begin_, p);
  return (dir_.VectMult(v1) == 0 && dir_.Scal(v1) >= 0);
}

geometry::Ray *geometry::Ray::Clone() const {
  return new Ray(begin_, dir_);
}

bool geometry::Ray::CrossesSegment(const geometry::Segment &s) const {
  if (s.ContainsPoint(begin_)) {
    return true;
  }
  Point tmp1 = begin_;
  tmp1 += dir_;
  Line line_vec(begin_, tmp1);
  if (!(line_vec.CrossesSegment(s))) {
    return false;
  }
  Vector seg_dir = s.GetEnd() - s.GetBeg();
  Vector temp_vec = begin_ - s.GetBeg();
  Vector tmp2 = dir_;
  int64_t mult1 = seg_dir.VectMult(temp_vec);
  int64_t mult2 = seg_dir.VectMult(tmp2);
  return mult1 * mult2 <= 0;
}

std::string geometry::Ray::ToString() const {
  std::string ret = "Ray(" + begin_.ToString() + ", " + dir_.ToString() + ")";
  return ret;
}

geometry::Point geometry::Ray::GetBegin() const {
  return begin_;
}

geometry::Vector geometry::Ray::GetDirection() const {
  return dir_;
}