#include "rational.h"
#include <numeric>
#include <cstdlib>

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(const int &a) : numerator_(a), denominator_(1) {
}

Rational::Rational(int a, int b) : numerator_(a), denominator_(b) {
  this->Reduction();
}

int32_t Rational::GetDenominator() const {
  return denominator_;
}

int32_t Rational::GetNumerator() const {
  return numerator_;
}

void Rational::SetDenominator(int den) {
  denominator_ = den;
  this->Reduction();
}

void Rational::SetNumerator(int num) {
  numerator_ = num;
  this->Reduction();
}

void Rational::Reduction() {
  if (denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  int gcd = std::gcd(std::abs(numerator_), std::abs(denominator_));
  numerator_ /= gcd;
  denominator_ /= gcd;
  if (denominator_ < 0) {
    denominator_ *= -1;
    numerator_ *= -1;
  }
}

Rational Rational::operator+(const Rational &oper) const {
  Rational ret(numerator_ * oper.denominator_ + denominator_ * oper.numerator_, denominator_ * oper.denominator_);
  ret.Reduction();
  return ret;
}

Rational Rational::operator-(const Rational &oper) const {
  Rational ret(numerator_ * oper.denominator_ - denominator_ * oper.numerator_, denominator_ * oper.denominator_);
  ret.Reduction();
  return ret;
}

Rational Rational::operator*(const Rational &oper) const {
  Rational ret(numerator_ * oper.numerator_, denominator_ * oper.denominator_);
  ret.Reduction();
  return ret;
}

Rational Rational::operator/(const Rational &oper) const {
  Rational ret(numerator_ * oper.denominator_, denominator_ * oper.numerator_);
  ret.Reduction();
  return ret;
}

Rational Rational::operator+() const {
  return {numerator_, denominator_};
}

Rational Rational::operator-() const {
  return {-numerator_, denominator_};
}

Rational &Rational::operator++() {
  numerator_ += denominator_;
  return *this;
}

Rational Rational::operator++(int) {
  auto old_value = *this;
  numerator_ += denominator_;
  return old_value;
}

Rational &Rational::operator--() {
  numerator_ -= denominator_;
  return *this;
}

Rational Rational::operator--(int) {
  auto old_value = *this;
  numerator_ -= denominator_;
  return old_value;
}

Rational &Rational::operator+=(const Rational &oper) {
  numerator_ = numerator_ * oper.denominator_ + denominator_ * oper.numerator_;
  denominator_ = denominator_ * oper.denominator_;
  this->Reduction();
  return *this;
}

Rational &Rational::operator-=(const Rational &oper) {
  numerator_ = numerator_ * oper.denominator_ - denominator_ * oper.numerator_;
  denominator_ = denominator_ * oper.denominator_;
  this->Reduction();
  return *this;
}

Rational &Rational::operator*=(const Rational &oper) {
  numerator_ *= oper.numerator_;
  denominator_ *= oper.denominator_;
  this->Reduction();
  return *this;
}

Rational &Rational::operator/=(const Rational &oper) {
  numerator_ *= oper.denominator_;
  denominator_ *= oper.numerator_;
  this->Reduction();
  return *this;
}

bool Rational::operator<(const Rational &oper) const {
  return (numerator_ * oper.denominator_ < denominator_ * oper.numerator_);
}

bool Rational::operator>(const Rational &oper) const {
  return (numerator_ * oper.denominator_ > denominator_ * oper.numerator_);
}

bool Rational::operator==(const Rational &oper) const {
  return (numerator_ * oper.denominator_ == denominator_ * oper.numerator_);
}

bool Rational::operator<=(const Rational &oper) const {
  return (numerator_ * oper.denominator_ <= denominator_ * oper.numerator_);
}

bool Rational::operator>=(const Rational &oper) const {
  return (numerator_ * oper.denominator_ >= denominator_ * oper.numerator_);
}

bool Rational::operator!=(const Rational &oper) const {
  return (numerator_ * oper.denominator_ != denominator_ * oper.numerator_);
}

std::ostream &operator<<(std::ostream &os, const Rational &r) {
  if (r.denominator_ == 1) {
    os << r.numerator_;
  } else {
    os << r.numerator_ << "/" << r.denominator_;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Rational &r) {
  const int max_size = 22;
  char str[max_size];
  is >> str;
  char *end = nullptr;
  r.numerator_ = strtoll(str, &end, 10);
  if (*end != 0) {
    ++end;
    r.denominator_ = strtoll(end, &end, 10);
  } else {
    r.denominator_ = 1;
  }
  r.Reduction();
  return is;
}

bool operator<(const int &a, Rational r) {
  Rational tmp(a);
  return (tmp < r);
}

bool operator>(const int &a, Rational r) {
  Rational tmp(a);
  return (tmp > r);
}

bool operator==(const int &a, Rational r) {
  Rational tmp(a);
  return (tmp == r);
}

bool operator!=(const int &a, Rational r) {
  Rational tmp(a);
  return (tmp != r);
}

bool operator>=(const int &a, Rational r) {
  Rational tmp(a);
  return (tmp >= r);
}

bool operator<=(const int &a, Rational r) {
  Rational tmp(a);
  return (tmp <= r);
}
