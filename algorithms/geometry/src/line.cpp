#include "../point.h"
#include "../vector.h"
#include "../line.h"
#include "../point.h"
#include "../segment.h"

geometry::Line::~Line() = default;

geometry::Line::Line() : a_(0), b_(0), c_(0) {
}

geometry::Line::Line(int64_t a, int64_t b, int64_t c) : a_(a), b_(b), c_(c) {
}

geometry::Line::Line(const geometry::Point &p1, const geometry::Point &p2) : a_(0), b_(0), c_(0) {
  if (p1.GetY() != p2.GetY() && p1.GetX() != p2.GetX()) {
    Vector dir = p2 - p1;
    a_ = -dir.GetJ();
    b_ = dir.GetI();
    c_ = -p1.GetX() * a_ - p1.GetY() * b_;
  } else if (p1.GetY() == p2.GetY()) {
    a_ = 0;
    b_ = 1;
    c_ = -p2.GetY();
  } else if (p1.GetX() == p2.GetX()) {
    a_ = 1;
    b_ = 0;
    c_ = -p2.GetX();
  }
}

geometry::Line &geometry::Line::Move(const geometry::Vector &v) {
  if (a_ * b_ != 0) {
    c_ = c_ - a_ * v.GetI() - b_ * v.GetJ();
  } else if (a_ == 0) {
    c_ -= v.GetJ();
  } else if (b_ == 0) {
    c_ -= v.GetI();
  }
  return *this;
}

geometry::Line *geometry::Line::Clone() const {
  return new Line(a_, b_, c_);
}

std::string geometry::Line::ToString() const {
  std::string ret = "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
  return ret;
}

bool geometry::Line::ContainsPoint(const geometry::Point &p) const {
  return a_ * p.GetX() + b_ * p.GetY() + c_ == 0;
}

bool geometry::Line::CrossesSegment(const geometry::Segment &s) const {
  return (PointVal(s.GetBeg()) * PointVal(s.GetEnd()) <= 0);
}

int64_t geometry::Line::PointVal(const geometry::Point &p) const {
  return a_ * p.GetX() + b_ * p.GetY() + c_;
}

int64_t geometry::Line::GetA() const {
  return a_;
}

int64_t geometry::Line::GetB() const {
  return b_;
}

geometry::Vector geometry::Line::NormalVector() const {
  return {a_, b_};
}