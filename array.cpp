#include <stdexcept>
#pragma once
#define ARRAY_TRAITS_IMPLEMENTED

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t N>
class Array {
 public:
  T array_[N];
  const T* Data() const {
    const T* ptr = array_;
    return ptr;
  }
  T* Data() {
    T* ptr = array_;
    return ptr;
  }
  T& Front() {
    return array_[0];
  }
  const T& Front() const {
    return array_[0];
  }
  T& Back() {
    return array_[N - 1];
  }
  const T& Back() const {
    return array_[N - 1];
  }
  size_t Size() const {
    return N;
  }
  bool Empty() const {
    return (N == 0);
  }
  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = value;
    }
  }
  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; i++) {
      auto tmp = other[i];
      other[i] = array_[i];
      array_[i] = tmp;
    }
  }
  const T& operator[](size_t idx) const {
    return array_[idx];
  }
  T& operator[](size_t idx) {
    return array_[idx];
  }
  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return array_[idx];
  }
  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return array_[idx];
  }
};

template <class T>
size_t GetSize(T) {
  return 0;
}

template <class T, size_t N>
size_t GetSize(T (&)[N]) {
  return N;
}

template <class T>
size_t GetRank(T) {
  return 0;
}

template <class T, size_t N>
size_t GetRank(T (&arr)[N]) {
  return 1 + GetRank(arr[0]);
}

template <class T>
size_t GetNumElements(T) {
  return 1;
}

template <class T, size_t N>
size_t GetNumElements(T (&arr)[N]) {
  return N * GetNumElements(arr[0]);
}
