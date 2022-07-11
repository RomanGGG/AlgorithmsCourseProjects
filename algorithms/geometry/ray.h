#pragma once
#include "IShape.h"
#include <memory>
#include <cstring>

class geometry::Ray : public geometry::IShape {
  Point begin_;
  Vector dir_;

 public:
  ~Ray() override;
  Ray();
  Ray(const Point&, const Point&);
  Ray(const Point&, const Vector&);
  Ray(const Ray&);

  //  Ray& operator=(const Ray&);

  Ray& Move(const Vector&) override;
  Ray* Clone() const override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::string ToString() const override;

  Point GetBegin() const;
  Vector GetDirection() const;
};