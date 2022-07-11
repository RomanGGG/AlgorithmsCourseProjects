#pragma once
#include "IShape.h"
#include <memory>
#include <cstring>

class geometry::Point : public geometry::IShape {
  int64_t x_;
  int64_t y_;

 public:
  Point();
  Point(const int64_t a, const int64_t b);
  ~Point() override = default;
  Point(const Point &other);

  Point &Move(const Vector &) override;
  Point *Clone() const override;
  std::string ToString() const override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;

  int64_t GetX() const;
  int64_t GetY() const;

  bool operator==(const Point &);
  Point &operator+=(const Vector &);
  geometry::Vector operator-(const geometry::Point &second) const;
};