#pragma once
#include <iostream>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
  int32_t numerator_;
  int32_t denominator_;
  friend std::ostream &operator<<(std::ostream &os, const Rational &r);
  friend std::istream &operator>>(std::istream &is, Rational &r);

 public:
  Rational();
  Rational(const int &a);  // NOLINT
  Rational(int a, int b);
  int32_t GetNumerator() const;
  int32_t GetDenominator() const;
  void SetNumerator(int num);
  void SetDenominator(int den);
  Rational operator+(const Rational &oper) const;
  Rational operator-(const Rational &oper) const;
  Rational operator*(const Rational &oper) const;
  Rational operator/(const Rational &oper) const;
  Rational &operator+=(const Rational &oper);
  Rational &operator-=(const Rational &oper);
  Rational &operator/=(const Rational &oper);
  Rational &operator*=(const Rational &oper);
  Rational operator+() const;
  Rational operator-() const;
  Rational &operator++();
  Rational &operator--();
  Rational operator++(int);
  Rational operator--(int);
  bool operator==(const Rational &oper) const;
  bool operator>=(const Rational &oper) const;
  bool operator<=(const Rational &oper) const;
  bool operator<(const Rational &oper) const;
  bool operator>(const Rational &oper) const;
  bool operator!=(const Rational &oper) const;
  void Reduction();
};

bool operator<(const int &a, Rational r);
bool operator>(const int &a, Rational r);
bool operator<=(const int &a, Rational r);
bool operator>=(const int &a, Rational r);
bool operator==(const int &a, Rational r);
bool operator!=(const int &a, Rational r);
