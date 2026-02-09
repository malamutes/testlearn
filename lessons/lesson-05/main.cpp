/*
Lesson 5 Objective:
Practice classes, constructors, and operators by building a tiny vector
math library (Vec2 + Vec3) with a small CLI demo.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic lessons/lesson-05/main.cpp -o lessons/lesson-05/main
  lessons/lesson-05/main
*/

#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <cstdint>
#include <array>

// powerful pattern that can generalise a lot of things including classes, builds generics
template <int Dimension>
class VectorN
{
public:
    std::array<double, Dimension> components;

    double getMagnitude()
    {
        double magnitude;
        for (int i = 0; i < components.size(); i++)
        {
            magnitude += std::pow(components[i], 2);
        }
        return std::sqrt(magnitude);
    }

    // need to turn the function into a template too
    double dotProduct(VectorN<Dimension> vector1, VectorN<Dimension> vector2)
    {
        int dotProduct;
        for (int i = 0; i < Dimension; i++)
        {
            dotProduct += vector1[i] * vector2[i];
        }

        return dotProduct;
    };

    std::array<double, Dimension> scalarMultiplication(double scalar)
    {
        std::array<double, Dimension> scaledArray;

        for (int i = 0; i < Dimension; i++)
        {
            scaledArray[i] = components[i] * scalar;
        }

        return scaledArray;
    }

    // get unit vector is the same as direction
    std::array<double, Dimension> getUnitVector()
    {
        if (getMagnitude() > 0)
        {
            return scalarMultiplication(1 / getMagnitude());
        }
        // aparrently cpp always initialize all arrays to 0? for number ish types
        return {};
    }

    bool isEqual(VectorN<Dimension> vector1, VectorN<Dimension> vector2)
    {
        // if not same then false, but this is wrong idk what to do
        if (Dimension != Dimension)
        {
            return false;
        }
        return (vector1.getMagnitude() == vector2.getMagnitude() && vector1.getUnitVector() == vector2.getUnitVector());
    }
};

class Vec2 : public VectorN<2>
{
public:
    double x;
    double y;

    // TODO: Constructors and methods.
    Vec2(double x, double y)
    {
        x = x;
        y = y;
    };
};

class Vec3 : public VectorN<3>
{
public:
    double x;
    double y;
    double z;

    // TODO: Constructors and methods.
    Vec3(double x, double y, double z)
    {
        x = x;
        y = y;
        z = z;
    };
};

double dotProductVec3(Vec3 v1, Vec3 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

double dotProductVec2(Vec2 v1, Vec2 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

int main()
{
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
    return 0;
}
