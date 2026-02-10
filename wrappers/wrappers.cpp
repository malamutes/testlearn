#include "wrappers.hpp"
#include <iostream>
#include <string>

// Use the namespace so the compiler knows this is the SAME printSimple
namespace MyWrappers {

void printSimple(std::string inputString) {
  std::cout << inputString << std::endl;
}

} // namespace MyWrappers