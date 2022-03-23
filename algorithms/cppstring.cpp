#include "cppstring.h"

size_t Strlen(const char *str) {
  size_t len = 0;
  const char *a = str;
  while (*a != '\0') {
    len++;
    a++;
  }
  return len;
}

String::~String() {
  delete[] str_;
}

String::String() : capacity_(1), size_(0), str_(nullptr) {
}

String::String(const String &other) {
  if (other.size_ == 0) {
    delete[] str_;
    size_ = 0;
    capacity_ = 1;
    str_ = nullptr;
  } else {
    str_ = new char[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (size_t i = 0; i < size_; i++) {
      str_[i] = other.str_[i];
    }
  }
}

String::String(size_t size, char symbol) : capacity_(2 * size), size_(size), str_(new char[capacity_]) {
  for (size_t i = 0; i < size; i++) {
    str_[i] = symbol;
  }
}

String::String(const char *str) : capacity_(2 * Strlen(str)), size_(Strlen(str)), str_(new char[capacity_]) {
  size_t len = Strlen(str);
  for (size_t i = 0; i < len; i++) {
    str_[i] = str[i];
  }
}

String::String(const char *str, size_t size) : capacity_(size), size_(size), str_(new char[capacity_]) {
  for (size_t i = 0; i < size; i++) {
    str_[i] = str[i];
  }
}

char &String::operator[](size_t idx) {
  return str_[idx];
}

const char &String::operator[](size_t idx) const {
  return str_[idx];
}

char &String::At(size_t idx) {
  if (idx >= size_) {
    throw StringOutOfRange();
  }
  return str_[idx];
}

const char &String::At(size_t idx) const {
  if (idx >= size_) {
    throw StringOutOfRange();
  }
  return str_[idx];
}

const char &String::Back() const {
  return str_[size_ - 1];
}

char &String::Back() {
  return str_[size_ - 1];
}

const char &String::Front() const {
  return str_[0];
}

char &String::Front() {
  return str_[0];
}

const char *String::CStr() const {
  return str_;
}

char *String::CStr() {
  return str_;
}

const char *String::Data() const {
  if (size_ == 0) {
    return nullptr;
  }
  return str_;
}

char *String::Data() {
  if (size_ == 0) {
    return nullptr;
  }
  return str_;
}

bool String::Empty() const {
  return (size_ == 0);
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return (capacity_ > 1) ? capacity_ : 0;
}

void String::Clear() {
  size_ = 0;
}

void String::PopBack() {
  size_ -= 1;
}

void String::PushBack(const char &symbol) {
  if (str_ == nullptr) {
    str_ = new char[1];
    str_[0] = symbol;
    size_ = 1;
    capacity_ = 1;
    return;
  }
  if (size_ < capacity_) {
    str_[size_] = symbol;
    size_++;
    return;
  }
  capacity_ *= 2;
  auto *tmp = new char[capacity_];
  for (size_t i = 0; i < size_; i++) {
    tmp[i] = str_[i];
  }
  tmp[size_] = symbol;
  size_++;
  delete[] str_;
  str_ = tmp;
}

void String::Swap(String &other) {
  auto *tmp1 = new char[other.capacity_];
  auto *tmp2 = new char[capacity_];
  for (size_t i = 0; i < other.size_; i++) {
    tmp1[i] = other[i];
  }
  for (size_t i = 0; i < size_; i++) {
    tmp2[i] = str_[i];
  }
  auto tmpcap = capacity_;
  auto tmpsize = size_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.size_ = tmpsize;
  other.capacity_ = tmpcap;
  delete[] str_;
  delete[] other.str_;
  str_ = tmp1;
  other.str_ = tmp2;
}

void String::ShrinkToFit() {
  capacity_ = size_;
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity > capacity_) {
    capacity_ = new_capacity;
  }
}

void String::Resize(size_t new_size, const char &symbol) {
  while (size_ < new_size) {
    this->PushBack(symbol);
  }
  while (size_ > new_size) {
    this->PopBack();
  }
}

String &String::operator=(const String &other) {
  String copy = other;
  Swap(copy);
  return *this;
}

String &String::operator+=(const String &other) {
  for (size_t i = 0; i < other.size_; i++) {
    this->PushBack(other.str_[i]);
  }
  return *this;
}

String operator+(const String &str1, const String &str2) {
  String a;
  a += str1;
  a += str2;
  return a;
}

bool String::operator>(const String &other) const {
  size_t s = (size_ < other.size_) ? size_ : other.size_;
  for (size_t i = 0; i < s; ++i) {
    if (str_[i] > other.str_[i]) {
      return true;
    }
    if (str_[i] < other.str_[i]) {
      return false;
    }
  }
  return size_ > other.size_;
}

bool String::operator<(const String &other) const {
  size_t s = (size_ < other.size_) ? size_ : other.size_;
  for (size_t i = 0; i < s; ++i) {
    if (str_[i] < other.str_[i]) {
      return true;
    }
    if (str_[i] > other.str_[i]) {
      return false;
    }
  }
  return (size_ < other.size_);
}

bool String::operator==(const String &other) const {
  if (size_ != other.size_) {
    return false;
  }
  for (size_t i = 0; i < size_; i++) {
    if (other.str_[i] != str_[i]) {
      return false;
    }
  }
  return true;
}

bool String::operator!=(const String &other) const {
  return !(*this == other);
}

bool String::operator<=(const String &other) const {
  return !(*this > other);
}

bool String::operator>=(const String &other) const {
  return !(*this < other);
}

std::istream &operator>>(std::istream &is, String &str) {
  for (size_t i = 0; i < str.size_; ++i) {
    is >> str[i];
  }
  return is;
}
std::ostream &operator<<(std::ostream &os, const String &str) {
  for (size_t i = 0; i < str.size_; ++i) {
    os << str[i];
  }
  return os;
}
