#include "../point.h"
#include "../vector.h"
#include "../segment.h"
#include "../line.h"

geometry::Segment::~Segment() = default;

geometry::Segment::Segment() : beg_({0, 0}), end_({0, 0}) {
}

geometry::Segment::Segment(const Point &a, const Point &b) : beg_(a), end_(b) {
}

geometry::Segment &geometry::Segment::Move(const geometry::Vector &v) {
  beg_.Move(v);
  end_.Move(v);
  return *this;
}

// ????

geometry::Segment *geometry::Segment::Clone() const {
  return new Segment(beg_, end_);
}

std::string geometry::Segment::ToString() const {
  std::string ret = "Segment(" + beg_.ToString() + ", " + end_.ToString() + ")";
  return ret;
}

bool geometry::Segment::ContainsPoint(const geometry::Point &p) const {
  return p.CrossesSegment(*this);
}

bool geometry::Segment::CrossesSegment(const geometry::Segment &s) const {
  Line l1(beg_, end_);
  Line l2(s.GetBeg(), s.GetEnd());
  if (!(l1.CrossesSegment(s) && l2.CrossesSegment(*this))) {
    return false;
  }
  bool flag1 = std::max(beg_.GetX(), end_.GetX()) >= std::min(s.GetBeg().GetX(), s.GetEnd().GetX());
  bool flag2 = std::max(beg_.GetY(), end_.GetY()) >= std::min(s.GetBeg().GetY(), s.GetEnd().GetY());
  return flag1 && flag2;
}

geometry::Point geometry::Segment::GetBeg() const {
  return beg_;
}

geometry::Point geometry::Segment::GetEnd() const {
  return end_;
}