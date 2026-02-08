/*
Lesson 2 Objective:
Learn functions, scope, and pass-by-value vs pass-by-reference.
You will build a unit converter with reusable functions.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic lessons/lesson-02/main.cpp -o lessons/lesson-02/main
  lessons/lesson-02/main
*/

#include <iostream>
#include <limits>

double c_to_f(double c)
{
  return (c * 9.0 / 5.0) + 32.0;
}

double f_to_c(double f)
{
  return (f - 32.0) * 5.0 / 9.0;
}

double km_to_mi(double km)
{
  return km * 0.621371;
}

double mi_to_km(double mi)
{
  return mi / 0.621371;
}

double kg_to_lb(double kg)
{
  return kg * 2.20462;
}

double lb_to_kg(double lb)
{
  return lb / 2.20462;
}

double cm_to_in(double cm)
{
  return cm / 2.54;
}

double in_to_cm(double in)
{
  return in * 2.54;
}

double l_to_gal(double l)
{
  return l * 0.264172;
}

double gal_to_l(double gal)
{
  return gal / 0.264172;
}

double perform_conversion(int choice, double value)
{
  switch (choice)
  {
  case 1:
    return c_to_f(value);
  case 2:
    return f_to_c(value);
  case 3:
    return km_to_mi(value);
  case 4:
    return mi_to_km(value);
  case 5:
    return kg_to_lb(value);
  case 6:
    return lb_to_kg(value);
  case 7:
    return cm_to_in(value);
  case 8:
    return in_to_cm(value);
  case 9:
    return l_to_gal(value);
  case 10:
    return gal_to_l(value);
  default:
    std::cerr << "Invalid conversion choice." << std::endl;
    return value;
  }
}

int main()
{
  // TODO: Implement the unit converter.
  // Requirements:
  // 1) Provide a menu of conversions (pick at least 5):
  //    - C <-> F
  //    - km <-> mi
  //    - kg <-> lb
  //    - cm <-> in
  //    - L <-> gal
  // 2) Each conversion must be a separate function:
  //    double c_to_f(double c), double f_to_c(double f), etc.
  // 3) Use pass-by-value for inputs, return the result.
  // 4) Input validation: handle non-numeric input and invalid menu choice.
  // 5) Loop until the user chooses to quit.
  // 6) Do NOT use global variables.

  int userInput = -1;
  double userNum = 0;
  double result = 0;
  bool exit = false;
  char userResponse;
  std::cout << "Lesson 2: implement the unit converter." << std::endl;

  while (!exit)
  {
    std::cout << "What conv;ersion would you like to perform? (Please select a number from 1-10). \n 1.) Celsius to Fahrenheit \n 2.) Fahrenheit to Celsius \n 3.) Kilometers to Miles \n 4.) Miles to Kilometers \n 5.) Kilograms to Pounds \n 6.) Pounds to Kilograms \n 7.) Centimeters to Inches \n 8.) Inches to Centimeters \n 9.) Liters to Gallons \n 10.) Gallons to Liters" << std::endl;

    while (!(std::cin >> userInput) || userInput < 1 || userInput > 10)
    {

      std::cout << "Invalid input. Please select a number from 1-10." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "You selected option " << userInput << "." << std::endl;

    std::cout << "Please enter the value you want to convert: " << std::endl;

    while (!(std::cin >> userNum))
    {
      std::cout << "Invalid input. Please enter a valid number: " << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    result = perform_conversion(userInput, userNum);

    std::cout << "The result is: " << result << std::endl;
    std::cout << "Do you want to perform another conversion? (y/n)" << std::endl;
    while (!(std::cin >> userResponse) || !(userResponse == 'y' || userResponse == 'Y' || userResponse == 'n' || userResponse == 'N'))
    {
      std::cout << "Invalid response. Please enter 'y' or 'n': " << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (userResponse == 'n' || userResponse == 'N')
    {
      exit = true;
    }
  }

  return 0;
}
