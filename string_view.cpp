#include <stdexcept>
#pragma once

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
  size_t len_ = 0;
  const char *str_ = nullptr;

 public:
  StringView() = default;
  StringView(const char *symbol) {  // NOLINT
    size_t len = 0;
    const char *a = symbol;
    while (*a != '\0') {
      len++;
      a++;
    }
    len_ = len;
    str_ = symbol;
  }
  StringView(const char *symbol, size_t len) : len_(len), str_(symbol) {
  }
  char At(size_t idx) const {
    if (idx >= len_) {
      throw StringViewOutOfRange();
    }
    return str_[idx];
  }
  char Front() const {
    return str_[0];
  }
  char Back() const {
    return str_[len_ - 1];
  }
  const char *Data() const {
    return str_;
  }
  bool Empty() const {
    return (len_ == 0);
  }
  size_t Size() const {
    return len_;
  }
  size_t Length() const {
    return len_;
  }
  char operator[](size_t idx) const {
    return str_[idx];
  }
  void Swap(StringView &other) {
    auto tmp = other.str_;
    other.str_ = str_;
    str_ = tmp;
    auto lentmp = other.len_;
    other.len_ = len_;
    len_ = lentmp;
  }
  void RemovePrefix(size_t prefix_size) {
    len_ -= prefix_size;
    str_ += prefix_size;
  }
  void RemoveSuffix(size_t suffix_size) {
    len_ -= suffix_size;
  }
  StringView Substr(size_t pos, size_t count = 1) {
    if (pos >= len_) {
      throw StringViewOutOfRange();
    }
    StringView substr(str_ + pos, (count < len_ - pos) ? count : len_ - pos);
    return substr;
  }
};
