#pragma once
#include <iostream>
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
  size_t capacity_ = 1;
  size_t size_ = 0;
  char *str_ = nullptr;

 public:
  String();
  String(size_t size, char symbol);
  String(const char *str);  // NOLINT
  String(const char *str, size_t size);
  ~String();
  String(const String &other);
  String &operator=(const String &other);
  const char &operator[](size_t idx) const;
  char &operator[](size_t idx);
  const char &At(size_t idx) const;
  char &At(size_t idx);
  const char &Front() const;
  char &Front();
  const char &Back() const;
  char &Back();
  const char *CStr() const;
  char *CStr();
  const char *Data() const;
  char *Data();
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String &other);
  void PopBack();
  void PushBack(const char &symbol);
  String &operator+=(const String &other);
  void Resize(size_t new_size, const char &symbol);
  void Reserve(size_t new_capacity);
  void ShrinkToFit();
  friend String operator+(const String &str1, const String &str2);
  bool operator>(const String &other) const;
  bool operator<(const String &other) const;
  bool operator>=(const String &other) const;
  bool operator<=(const String &other) const;
  bool operator==(const String &other) const;
  bool operator!=(const String &other) const;
  friend std::istream &operator>>(std::istream &is, String &str);
  friend std::ostream &operator<<(std::ostream &os, const String &str);
};
