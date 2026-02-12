#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// g++ -std=c++14 -Wall -Wextra -pedantic math/derivative.cpp -o math/derivative; math/derivative

struct polynomial_node {
    float constant;
    float exponent;
};

template <int Terms> class PolynomialFunction {
  public:
    std::array<polynomial_node, Terms + 1> polynomial_function{};
    char symbol;

    // will be placed right to left (i.e right most index is highest)
    PolynomialFunction(char symbolInit, std::array<int, Terms + 1> constants) {
        for (uint16_t i = 0; i < constants.size(); i++) {
            // current constant is zero, so empty
            // need to subtract back 1 to account for the constant
            polynomial_node currentNode;
            if (constants[i] == 0) {
                currentNode.constant = 0;
                currentNode.exponent = i;
            } else {
                currentNode.constant = constants[i];
                currentNode.exponent = i;
            }
            polynomial_function[i] = currentNode;
        };

        symbol = symbolInit;
    }

    void printPolynomialFunction(bool plusC = false) const {
        std::string pFunc;

        for (uint16_t i = 0; i < polynomial_function.size(); i++) {
            float coeff = polynomial_function[i].constant;
            float exp = polynomial_function[i].exponent;

            if (coeff == 0)
                continue;

            // 1. Handle the Plus/Minus signs between terms
            if (!pFunc.empty() && coeff > 0) {
                pFunc += " + ";
            } else if (coeff < 0) {
                pFunc += " - ";
                coeff = -coeff; // Work with absolute value for the rest of the loop
            }

            // 2. Use ostringstream to strip zeros from the coefficient
            std::ostringstream ossCoeff;
            ossCoeff << coeff;
            pFunc += ossCoeff.str();

            // 3. Handle the variable and exponent
            if (exp != 0) {
                pFunc += symbol;

                if (exp != 1) {
                    pFunc += "^";
                    std::ostringstream ossExp;
                    ossExp << exp;
                    pFunc += ossExp.str();
                }
            }
        }

        if (plusC) {
            pFunc += ' ';
            pFunc += '+';
            pFunc += ' ';
            pFunc += 'C';
        }

        if (pFunc.empty())
            pFunc = "0"; // Handle the case where the function is just 0

        std::cout << "The polynomial function is: " << pFunc << std::endl;
    }

    void getPolyValueAtInput(double value) const {
        double result = 0;
        for (uint16_t i = 0; i < polynomial_function.size(); i++) {
            result +=
                polynomial_function[i].constant * std::pow(value, polynomial_function[i].exponent);
        }

        std::cout << "The polynomial at input = " << value << " is " << result << std::endl;
    }

    PolynomialFunction<Terms> getDerivative() const {
        std::array<int, Terms + 1> polyInitArray{};
        PolynomialFunction<Terms> derivPolyFunc(symbol, polyInitArray);

        for (uint16_t i = 0; i < polynomial_function.size(); i++) {
            if (polynomial_function[i].exponent - 1 < 0) {
                derivPolyFunc.polynomial_function[i].exponent = 0;
                derivPolyFunc.polynomial_function[i].constant = 0;
            } else {
                derivPolyFunc.polynomial_function[i].exponent = polynomial_function[i].exponent - 1;
                derivPolyFunc.polynomial_function[i].constant =
                    polynomial_function[i].exponent * polynomial_function[i].constant;
            }
        }

        return derivPolyFunc;
    }

    PolynomialFunction<Terms> getIntegral() const {
        std::array<int, Terms + 1> polyInitArray{};
        PolynomialFunction<Terms> integratePolyFunc(symbol, polyInitArray);

        for (uint16_t i = 0; i < polynomial_function.size(); i++) {
            integratePolyFunc.polynomial_function[i].exponent = polynomial_function[i].exponent + 1;
            integratePolyFunc.polynomial_function[i].constant =
                polynomial_function[i].constant / (polynomial_function[i].exponent + 1);
        }

        return integratePolyFunc;
    }

    template <int OtherTermSize>
    PolynomialFunction<std::max(OtherTermSize, Terms)>
    operator+(const PolynomialFunction<OtherTermSize> &other) const {
        // no idea waht constexpr is, need to look it up, geimini said to use
        constexpr int ResultSize = std::max(Terms, OtherTermSize);
        std::array<int, ResultSize + 1> polyInitArray{};

        // for now assume symbols are just the same 'x' we can do a case for them being different
        // later
        PolynomialFunction<ResultSize> sumPoly(symbol, polyInitArray);

        //+1 is to account for constant terms
        for (uint16_t i = 0; i < ResultSize + 1; i++) {
            bool inThis = (i <= Terms);
            bool inOther = (i <= OtherTermSize);
            // same exponent, add, they should be, because the array is dense
            // an idea to explore is to keep sparse arrays and then keep two counters,
            // increment one regularly and the other is just to verify exponent equality
            if (inThis && inOther) {
                // both have this exponent
                sumPoly.polynomial_function[i].exponent = other.polynomial_function[i].exponent;
                sumPoly.polynomial_function[i].constant =
                    other.polynomial_function[i].constant + polynomial_function[i].constant;
            }
            // only one of them have it so add the one that has it
            else if (inThis) {
                sumPoly.polynomial_function[i].exponent = polynomial_function[i].exponent;
                sumPoly.polynomial_function[i].constant = polynomial_function[i].constant;
            } else if (inOther) {
                sumPoly.polynomial_function[i].exponent = other.polynomial_function[i].exponent;
                sumPoly.polynomial_function[i].constant = other.polynomial_function[i].constant;
            }
        }
        return sumPoly;
    }

    template <int OtherTermSize>
    PolynomialFunction<std::max(OtherTermSize, Terms)>
    operator-(const PolynomialFunction<OtherTermSize> &other) const {
        // no idea waht constexpr is, need to look it up, geimini said to use
        constexpr int ResultSize = std::max(Terms, OtherTermSize);
        std::array<int, ResultSize + 1> polyInitArray{};

        // for now assume symbols are just the same 'x' we can do a case for them being different
        // later
        PolynomialFunction<ResultSize> sumPoly(symbol, polyInitArray);

        //+1 is to account for constant terms
        for (uint16_t i = 0; i < ResultSize + 1; i++) {
            bool inThis = (i <= Terms);
            bool inOther = (i <= OtherTermSize);
            // same exponent, add, they should be, because the array is dense
            // an idea to explore is to keep sparse arrays and then keep two counters,
            // increment one regularly and the other is just to verify exponent equality
            if (inThis && inOther) {
                // both have this exponent
                sumPoly.polynomial_function[i].exponent = other.polynomial_function[i].exponent;
                sumPoly.polynomial_function[i].constant =
                    other.polynomial_function[i].constant - polynomial_function[i].constant;
            }
            // only one of them have it so add the one that has it
            // needs to be negative because its essentially 0 minus that
            // and if negativbe its flipped
            else if (inThis) {
                sumPoly.polynomial_function[i].exponent = polynomial_function[i].exponent;
                sumPoly.polynomial_function[i].constant = -polynomial_function[i].constant;
            } else if (inOther) {
                sumPoly.polynomial_function[i].exponent = other.polynomial_function[i].exponent;
                sumPoly.polynomial_function[i].constant = -other.polynomial_function[i].constant;
            }
        }
        return sumPoly;
    }
};

int main() {
    char symbol = 'x';
    // highest order on the right, lowest on the left
    std::array<int, 5> polyInitArray = {4, 0, -2, -5, -10};
    PolynomialFunction<4> poly_func(symbol, polyInitArray);

    std::array<int, 6> polyInitArray_one = {25, -5, 0, -10, 0, 4};
    PolynomialFunction<5> poly_func_one(symbol, polyInitArray_one);

    PolynomialFunction<5> poly_func_res = poly_func_one + poly_func;
    PolynomialFunction<5> poly_func_res_minus = poly_func_one - poly_func;

    poly_func.printPolynomialFunction();
    poly_func_one.printPolynomialFunction();
    // poly_func_res.printPolynomialFunction();
    poly_func_res_minus.printPolynomialFunction();
    poly_func_res_minus.getIntegral().printPolynomialFunction(true);
    poly_func_res_minus.getDerivative().printPolynomialFunction();

    return 0;
}