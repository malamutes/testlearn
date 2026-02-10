/*
Lesson 5 Objective:
Practice classes, constructors, and operators by building a tiny vector
math library (Vec2 + Vec3) with a small CLI demo.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic -I wrappers/ lessons/lesson-05/main.cpp
wrappers/wrappers.cpp -o lessons/lesson-05/main;   lessons/lesson-05/main
*/

#include "wrappers.hpp"
#include <array>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

// powerful pattern that can generalise a lot of things including classes,
// builds generics
template <int Dimension> class VectorN {
public:
  std::array<double, Dimension> components{};

  double getMagnitude() {
    double magnitude = 0.0;
    for (size_t i = 0; i < components.size(); i++) {
      magnitude += std::pow(components[i], 2);
    }

    return std::sqrt(magnitude);
  }

  // need to turn the function into a template too
  double dotProduct(const VectorN<Dimension> &vector2) {
    double dotProduct = 0.0;
    for (int i = 0; i < Dimension; i++) {
      dotProduct += components[i] * vector2.components[i];
    }

    return dotProduct;
  };

  std::array<double, Dimension> scalarMultiplication(double scalar) {
    std::array<double, Dimension> scaledArray;

    for (int i = 0; i < Dimension; i++) {
      scaledArray[i] = components[i] * scalar;
    }

    return scaledArray;
  }

  // get unit vector is the same as direction
  std::array<double, Dimension> getUnitVector() {
    if (getMagnitude() > 0) {
      return scalarMultiplication(1 / getMagnitude());
    }
    // aparrently cpp always initialize all arrays to 0? for number ish types
    return {};
  }

  bool isEqual(const VectorN<Dimension> &vectorToCompare) {
    // if not same then false, but this is wrong idk what to do
    for (size_t i = 0; i < Dimension; ++i) {
      if (components[i] != vectorToCompare.components[i])
        return false;
    }

    return true;
  }

  std::array<double, Dimension> vectorAdd(const VectorN<Dimension> &other) {
    std::array<double, Dimension> sumArray;

    for (int i = 0; i < Dimension; i++) {
      sumArray[i] = components[i] + other.components[i];
    }

    return sumArray;
  }

  std::array<double, Dimension> operator+(const VectorN<Dimension> &other) {
    std::array<double, Dimension> sumArray;

    for (int i = 0; i < Dimension; i++) {
      sumArray[i] = components[i] + other.components[i];
    }

    return sumArray;
  }

  std::array<double, Dimension>
  vectorSubtract(const VectorN<Dimension> &other) {
    std::array<double, Dimension> subtractArray;

    for (int i = 0; i < Dimension; i++) {
      subtractArray[i] = components[i] - other.components[i];
    }

    return subtractArray;
  }

  std::array<double, Dimension> operator-(const VectorN<Dimension> &other) {
    std::array<double, Dimension> subtractArray;

    for (int i = 0; i < Dimension; i++) {
      subtractArray[i] = components[i] - other.components[i];
    }

    return subtractArray;
  }
};

class Vec2 : public VectorN<2> {
public:
  Vec2(double x, double y) {
    components[0] = x;
    components[1] = y;
  }
};

class Vec3 : public VectorN<3> {
public:
  Vec3(double x, double y, double z) {
    components[0] = x;
    components[1] = y;
    components[2] = z;
  }
};

int main() {
  // TODO: Implement the vector math library demo.
  // Requirements:
  // 1) Implement Vec2 and Vec3 with:
  //    - default constructor (0,0 / 0,0,0)
  //    - parameterized constructor
  //    - magnitude()
  //    - normalize() (handle zero vector safely)
  //    - dot(const VecN& other)
  // 2) Implement operators for Vec2 and Vec3:
  //    - + and - between two vectors
  //    - * by scalar (vector * scalar)
  // 3) For Vec3, implement cross(const Vec3& other).
  // 4) Provide a small CLI demo that:
  //    - reads two vectors from input
  //    - prints magnitude, dot, and (for Vec3) cross
  //    - shows normalization result
  // 5) Input validation for numeric entries.
  // 6) No global variables.

  std::cout << "Lesson 5: implement the vector math library." << std::endl;

  Vec3 vector3a = Vec3(10, -9.2, 1.6);
  Vec3 vector3b = Vec3(10, -9.2, 1.6);

  MyWrappers::printWithArg("return boolean", (vector3a.dotProduct(vector3b)));

  MyWrappers::printArray(vector3a + vector3b);

  MyWrappers::printArray(vector3a - vector3b);

  return 0;
}
