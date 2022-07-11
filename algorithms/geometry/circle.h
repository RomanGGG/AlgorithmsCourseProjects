#pragma once
#include "IShape.h"
#include "point.h"

class geometry::Circle : public geometry::IShape {
 private:
  Point cent_;
  int64_t rad_;

 public:
  ~Circle() override;
  Circle(const Point &, int64_t r);
  Circle(const Circle &);

  Circle &Move(const Vector &) override;
  Circle *Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
};