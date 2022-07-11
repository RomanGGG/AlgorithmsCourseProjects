#pragma once
#include "IShape.h"
#include <memory>
#include <cstring>
#include <bits/stl_vector.h>

class geometry::Polygon : public geometry::IShape {
  std::vector<Point> points_;

 public:
  explicit Polygon(std::vector<Point>);

  Polygon& Move(const Vector&) override;
  Polygon* Clone() const override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::string ToString() const override;
};