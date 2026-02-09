#include <iostream>
#include <new>
#include <cstdint>
#include <limits>
#include <string>

using namespace std;

struct Arena_Mem {
    char* start;
    size_t mem_size;
    char* current;
};

void print(string inputString) {
    cout << inputString << endl;
};

template<typename T>

//only for non strings, i.e. float, double, int, char
void captureUserInput(string queryString, T& varToStore) {
    print(queryString);

    while(!(cin >> varToStore)) {
        print("Invalid input, please re-enter input: ");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    print("Input has been collected");
};   

void AllocateMemory(size_t size_to_allocate, Arena_Mem arena) {
    if((arena.current + size_to_allocate) > (arena.start + arena.mem_size)) {
        //block to allcoat eis out of bounde, errr
    }
    else {
        arena.current += size_to_allocate;
        print("Memory has been allocated and is within buffer founds.");
    }
}

int main() {

    bool exit = false;
    size_t memorySpace;
    Arena_Mem arena;
    char userInput;

    captureUserInput("Please enter the size of the Arena: ", memorySpace);

    while(!exit) {
        print("Please select an option from the menu below.");

        if(!(cin >> userInput) ||    (userInput < 0) || (userInput > 9)) {
            print("Invalid selection, please ensure your input is correct.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << userInput << endl;  

        if(userInput == 9) {
            exit = true;
        }

    }
     
    return 0;
}