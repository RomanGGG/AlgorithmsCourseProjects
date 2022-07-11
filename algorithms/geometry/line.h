#pragma once
#include "IShape.h"
#include "point.h"

class geometry::Line : public geometry::IShape {
 private:
  int64_t a_;
  int64_t b_;
  int64_t c_;

 public:
  ~Line() override;
  Line();
  Line(int64_t a, int64_t b, int64_t c);
  Line(const Point&, const Point&);

  Line& Move(const Vector&) override;
  Line* Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;

  int64_t PointVal(const Point&) const;

  int64_t GetA() const;
  int64_t GetB() const;

  Vector NormalVector() const;
};