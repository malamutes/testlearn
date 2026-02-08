/*
Lesson 1 Objective:
Build a tiny command-line calculator that reads two numbers and an operator,
validates input, performs the operation, and repeats until the user quits.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic lessons/lesson-01/main.cpp -o lessons/lesson-01/main
  lessons/lesson-01/main
*/

#include <iostream>
#include <limits>
int main()
{
    // TODO: Implement the interactive calculator.
    // Requirements:
    // 1) Ask for first number (double).
    // 2) Ask for operator: +, -, *, /
    // 3) Ask for second number (double).
    // 4) Validate input: if cin fails, clear and re-prompt.
    // 5) Division by zero should show an error and re-prompt for second number.
    // 6) After showing result, ask "Again? (y/n)" and loop accordingly.

    std::cout << "Lesson 1: implement the calculator." << std::endl;
    double firstNum = 0;
    double secondNum = 0;
    char userSelectedOperand;
    double result = 0;
    bool exit = false;
    char userResponse;

    while (!exit)
    {
        std::cout << "Enter the first number: " << std::endl;
        while (!(std::cin >> firstNum))
        {
            std::cout << "Invalid input. Please enter a valid number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "What is the operand? (Please use +, -, *, /)" << std::endl;

        while (!(std::cin >> userSelectedOperand) || !(userSelectedOperand == '+' || userSelectedOperand == '-' || userSelectedOperand == '*' || userSelectedOperand == '/'))
        {
            std::cout << "Invalid operand selected. Please select the correct operand (+, -, *, /)." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter the second number: " << std::endl;

        while (!(std::cin >> secondNum))
        {
            std::cout << "Invalid input. Please enter a valid number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (userSelectedOperand)
        {
        case '+':
            result = firstNum + secondNum;
            break;
        case '-':
            result = firstNum - secondNum;
            break;
        case '*':
            result = firstNum * secondNum;
            break;
        case '/':
            if (secondNum == 0)
            {
                std::cout << "Error: Division by zero is not allowed." << std::endl;
                while (secondNum == 0)
                {
                    std::cout << "Please enter a non-zero number for the second number: " << std::endl;
                    while (!(std::cin >> secondNum))
                    {
                        std::cout << "Invalid input. Please enter a valid number: " << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }
            result = firstNum / secondNum;
            break;
        }

        std::cout << "The result is: " << result << std::endl;
        std::cout << "Again? (y/n)" << std::endl;
        std::cin >> userResponse;
        if (userResponse == 'y' || userResponse == 'Y')
        {
            exit = false;
        }
        else if (userResponse == 'n' || userResponse == 'N')
        {
            exit = true;
        }
        else
        {
            std::cout << "Invalid response. Exiting." << std::endl;
            exit = true;
        }
    }

    return 0;
}
