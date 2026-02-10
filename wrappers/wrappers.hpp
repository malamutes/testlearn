#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <iostream>
#include <string>

namespace MyWrappers {
void printSimple(std::string inputString);

template <typename T>
void printWithArg(std::string inputString, const T &optionalArg) {
  std::cout << inputString << ": " << optionalArg << std::endl;
};

template <size_t Size> void printArray(const std::array<double, Size> &arr) {
  std::cout << "Array: (";
  for (size_t i = 0; i < Size; ++i) {
    std::cout << arr[i] << (i == Size - 1 ? "" : ", ");
  }
  std::cout << ")" << std::endl;
}
} // namespace MyWrappers

#endif