/*
Lesson 4 Objective:
Practice std::vector and basic algorithms by building a gradebook.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic lessons/lesson-04/main.cpp -o lessons/lesson-04/main
  lessons/lesson-04/main
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Student
{
    std::string name;
    std::vector<double> scores;
};

int main()
{
    // TODO: Implement the gradebook.
    // Requirements:
    // 1) Maintain a std::vector<Student>.
    // 2) Menu options (at least):
    //    - Add student
    //    - Add score to student
    //    - Compute average for a student
    //    - List students sorted by name
    //    - Remove student
    //    - Quit
    // 3) Input validation for menu and numeric entries.
    // 4) Use std::sort for listing by name.
    // 5) No global variables.

    int userInput;
    bool exit = false;
    std::vector<Student> students;
    std::cout << "Lesson 4: implement the gradebook." << std::endl;
    while (!exit)
    {
        std::cout << "Menu options for student bookkeeping program: \n 1. Add student \n 2. Add score to student \n 3. Compute average for a student \n 4. List students sorted by name \n 5. Remove student \n 6. Quit" << std::endl;
        while (!(std::cin >> userInput) || userInput < 1 || userInput > 6)
        {
            std::cout << "Invalid input. Please enter a number between 1 and 6: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "You selected option " << userInput << std::endl;

        if (userInput == 1)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string studentName;
            std::cout << "Enter student name: ";
            std::getline(std::cin, studentName, '\n');
            if (studentName.empty())
            {
                std::cout << "Input cannot be empty. Please enter a line of text:" << std::endl;
                continue;
            }

            std::cout << "The student name is " << studentName << std::endl;
            Student newStudent = {studentName, {}};
            students.push_back(newStudent);
        }
        else if (userInput == 2)
        {
            bool found = false;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string studentName;
            std::cout << "Enter student name: ";
            std::getline(std::cin, studentName, '\n');
            if (studentName.empty())
            {
                std::cout << "Input cannot be empty. Please enter a line of text:" << std::endl;
                continue;
            }

            double studentScore;
            for (Student &student : students)
            {
                if (student.name == studentName)
                {
                    std::cout << "Add a student score:" << std::endl;
                    while (!(std::cin >> studentScore))
                    {
                        std::cout << "Please enter a valid student score..." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    student.scores.push_back(studentScore);
                    found = true;
                    break;
                }
            }

            if (found)
            {
                std::cout << "Student score has been added" << std::endl;
            }
            else
            {
                std::cout << "No student is found!" << std::endl;
            }
        }
        else if (userInput == 3)
        {

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string studentName;
            std::cout << "Enter student name: ";

            std::getline(std::cin, studentName, '\n');
            if (studentName.empty())
            {
                std::cout << "Input cannot be empty. Please enter a line of text:" << std::endl;
                continue;
            }

            bool found = false;
            int numScores;
            double avgScore = 0;
            for (const Student &student : students)
            {
                if (student.name == studentName)
                {
                    numScores = student.scores.size();
                    found = true;
                    if (student.scores.empty())
                    {
                        std::cout << "This student has no listed scores!" << std::endl;
                        break;
                    }
                    for (double score : student.scores)
                    {
                        avgScore += score;
                    }
                    std::cout << "The avg score for student " << studentName << " is " << avgScore / numScores << std::endl;
                    break;
                }
            }

            if (!found)
            {
                std::cout << "No student with such a name is found!" << std::endl;
            }
        }
        else if (userInput == 4)
        {
            std::cout << "Listing students sorted by name alphabetically : " << std::endl;
            std::vector<Student> sortedStudents = students;
            std::sort(sortedStudents.begin(), sortedStudents.end(), [](const Student &a, const Student &b)
                      { return a.name < b.name; });

            std::cout << "\n--- Students Listed in Order ---" << std::endl;

            if (sortedStudents.empty())
            {
                std::cout << "No students found in the system." << std::endl;
            }
            else
            {
                for (const auto &student : sortedStudents)
                { // 'auto' is like TypeScript 'let' but for types
                    std::cout << "Name: " << student.name << " | ";

                    if (student.scores.empty())
                    {
                        std::cout << "No scores recorded.";
                    }
                    else
                    {
                        std::cout << "Scores: " << student.scores.size();
                    }
                    std::cout << std::endl;
                }
            }
        }
        else if (userInput == 5)
        {

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string studentName;
            std::cout << "Enter student name: ";
            std::getline(std::cin, studentName, '\n');
            if (studentName.empty())
            {
                std::cout << "Input cannot be empty. Please enter a line of text:" << std::endl;
                continue;
            }
            bool found = false;
            for (size_t i = 0; i < students.size(); ++i)
            {
                if (students[i].name == studentName)
                {
                    students.erase(students.begin() + i);
                    found = true;
                    break;
                }
            }

            if (found)
            {
                std::cout << "Student has been deleted." << std::endl;
            }
            else
            {
                std::cout << "No such student is found" << std::endl;
            }
        }
        else if (userInput == 6)
        {
            exit = true;
        }
    }

    return 0;
}
