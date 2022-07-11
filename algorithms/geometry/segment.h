#pragma once
#include "IShape.h"
#include "point.h"

class geometry::Segment : public geometry::IShape {
 private:
  geometry::Point beg_;
  geometry::Point end_;

 public:
  ~Segment() override;
  Segment();
  Segment(const Point&, const Point&);
  Point GetBeg() const;
  Point GetEnd() const;
  Segment& Move(const Vector&) override;
  Segment* Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
};