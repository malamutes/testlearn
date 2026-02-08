/*
Lesson 3 Objective:
Practice arrays and strings by building a simple text analyzer.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic lessons/lesson-03/main.cpp -o lessons/lesson-03/main
  lessons/lesson-03/main
*/

#include <iostream>
#include <limits>
#include <string>

int main()
{
  // TODO: Implement the text analyzer.
  // Requirements:
  // 1) Read a full line of text (use std::getline).
  // 2) Count:
  //    - total characters (including spaces)
  //    - total alphabetic characters (A-Z, a-z)
  //    - total digits (0-9)
  //    - total whitespace characters (space, tab, etc.)
  //    - total words (sequences of non-whitespace)
  // 3) Also track frequency of each vowel (a, e, i, o, u) case-insensitive.
  // 4) Use a fixed-size array for vowel counts (size 5).
  // 5) Input validation: if the line is empty, prompt again.
  // 6) Loop until the user chooses to quit.

  std::string input;
  std::cout << "Lesson 3: implement the text analyzer." << std::endl;
  std::cout << "Please enter a line of text" << std::endl;
  bool exit = false;
  char userInput;
  int numCharacters = 0;
  int totalDigits = 0;
  int totalAphabetic = 0;
  int totalWhitespace = 0;
  int totalWords = 0;
  int vowelCounts[5] = {0, 0, 0, 0, 0};

  while (!exit)
  {
    std::getline(std::cin, input, '\n');
    if (input.empty())
    {
      std::cout << "Input cannot be empty. Please enter a line of text:" << std::endl;
      continue;
    }

    numCharacters = input.length();
    totalDigits = 0;
    totalAphabetic = 0;
    totalWhitespace = 0;
    totalWords = 0;
    for (int i = 0; i < 5; i++)
    {
      vowelCounts[i] = 0;
    }

    bool inWord = false;
    for (int i = 0; i < input.length(); i++)
    {
      char c = input[i];
      if (std::isdigit(c))
      {
        totalDigits++;
      }
      else if (std::isalpha(c))
      {
        totalAphabetic++;
        char lowerC = std::tolower(c);
        if (lowerC == 'a')
        {
          vowelCounts[0]++;
        }
        else if (lowerC == 'e')
        {
          vowelCounts[1]++;
        }
        else if (lowerC == 'i')
        {
          vowelCounts[2]++;
        }
        else if (lowerC == 'o')
        {
          vowelCounts[3]++;
        }
        else if (lowerC == 'u')
        {
          vowelCounts[4]++;
        }
      }
      else if (std::isspace(c))
      {
        totalWhitespace++;
      }

      if (!inWord && !std::isspace(c))
      {
        inWord = true;
        totalWords++;
      }
      else if (inWord && std::isspace(c))
      {
        inWord = false;
      }
    }

    std::cout << "You entered: " << input << std::endl;
    std::cout << "Number of characters: " << numCharacters << std::endl;
    std::cout << "Number of digits: " << totalDigits << std::endl;
    std::cout << "Number of alphabetic characters: " << totalAphabetic << std::endl;
    std::cout << "Number of whitespace characters: " << totalWhitespace << std::endl;
    std::cout << "Number of words: " << totalWords << std::endl;
    std::cout << "Vowel counts:" << std::endl;
    const char *vowels[] = {"a", "e", "i", "o", "u"};
    for (int i = 0; i < 5; i++)
    {
      std::cout << vowels[i] << ": " << vowelCounts[i] << std::endl;
    }

    std::cout << "Do you want to analyze another line? (y/n): ";
    while (!(std::cin >> userInput) || (userInput != 'y' && userInput != 'n'))
    {
      std::cout << "Invalid input. Please enter 'y' or 'n': ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter your next line of text:" << std::endl;
    if (userInput == 'n')
    {
      exit = true;
    }
  }

  return 0;
}
