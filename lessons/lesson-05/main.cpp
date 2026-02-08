/*
Lesson 5 Objective:
Practice classes, constructors, and business rules by building a simple
subscription billing system.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic lessons/lesson-05/main.cpp -o lessons/lesson-05/main
  lessons/lesson-05/main
*/

#include <iostream>
#include <limits>
#include <string>
#include <vector>

class Subscription
{
public:
    std::string customer;
    std::string plan; // "Basic", "Pro", or "Enterprise"
    int seats;
    double monthly_rate;
    bool active;

    // TODO: Add constructors and methods.
};

int main()
{
    // TODO: Implement the subscription billing system.
    // Requirements:
    // 1) Maintain a std::vector<Subscription>.
    // 2) Menu options (at least):
    //    - Add subscription
    //    - Change plan
    //    - Add/remove seats
    //    - Cancel subscription
    //    - Reactivate subscription
    //    - Show monthly bill for a customer
    //    - List all active subscriptions
    //    - Quit
    // 3) Business rules:
    //    - seats must be >= 1 for active subscriptions
    //    - inactive subscriptions have 0 seats and $0 monthly bill
    //    - plan determines base monthly_rate (you choose rates)
    // 4) Use constructors to ensure valid initial state.
    // 5) Use methods on Subscription to enforce rules (e.g., set_plan, set_seats, cancel).
    // 6) Input validation for menu and numeric entries.
    // 7) No global variables.

    std::cout << "Lesson 5: implement the subscription billing system." << std::endl;
    return 0;
}
