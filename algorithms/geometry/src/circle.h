#include "../point.h"
#include "../vector.h"
#include "../circle.h"
#include "../segment.h"
#include "../line.h"

geometry::Circle::Circle(const geometry::Point &p, int64_t r) : cent_(p), rad_(r) {
}

geometry::Circle::~Circle() = default;

geometry::Circle::Circle(const geometry::Circle &c) : cent_(c.cent_), rad_(c.rad_) {
}

geometry::Circle &geometry::Circle::Move(const geometry::Vector &v) {
  cent_ += v;
  return *this;
}

geometry::Circle *geometry::Circle::Clone() const {
  return new Circle(cent_, rad_);
}

std::string geometry::Circle::ToString() const {
  std::string ret = "Circle(" + cent_.ToString() + ", " + std::to_string(rad_) + ")";
  return ret;
}

bool geometry::Circle::ContainsPoint(const geometry::Point &p) const {
  return (rad_ * rad_ >= (p.GetX() - cent_.GetX()) * (p.GetX() - cent_.GetX()) +
                             (p.GetY() - cent_.GetY()) * (p.GetY() - cent_.GetY()));
}

bool geometry::Circle::CrossesSegment(const geometry::Segment &s) const {
  if ((ContainsPoint(s.GetBeg()) && !ContainsPoint(s.GetEnd())) ||
      (!ContainsPoint(s.GetBeg()) && ContainsPoint(s.GetEnd()))) {
    return true;
  }
  auto p = s.GetBeg();
  auto p2 = s.GetEnd();
  int64_t len1 =
      (p.GetX() - cent_.GetX()) * (p.GetX() - cent_.GetX()) + (p.GetY() - cent_.GetY()) * (p.GetY() - cent_.GetY());
  int64_t len2 =
      (p2.GetX() - cent_.GetX()) * (p2.GetX() - cent_.GetX()) + (p2.GetY() - cent_.GetY()) * (p2.GetY() - cent_.GetY());
  if (len1 < rad_ * rad_ && len2 < rad_ * rad_) {
    return false;
  }
  Line segment_dir(s.GetBeg(), s.GetEnd());
  int64_t value = segment_dir.PointVal(cent_);
  int64_t len = value * value;
  if (len > rad_ * rad_ * (segment_dir.GetA() * segment_dir.GetA() + segment_dir.GetB() * segment_dir.GetB())) {
    return false;
  }
  Vector other_normal = segment_dir.NormalVector();
  Line normal_line(cent_, {cent_.GetX() + other_normal.GetI(), cent_.GetY() + other_normal.GetJ()});
  return normal_line.CrossesSegment(s);
}
