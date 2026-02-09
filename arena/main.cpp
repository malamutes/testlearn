// KEEP TO IMPROVE

#include <iostream>
#include <new>
#include <cstdint>
#include <limits>
#include <string>

using namespace std;

struct Arena_Mem
{
    char *start;
    size_t mem_size;
    char *current;
};

// only string, simple print
void printSimple(string inputString)
{
    cout << inputString << endl;
}

template <typename T>
void printWithArg(string inputString, const T &optionalArg)
{
    cout << inputString << ": " << optionalArg << endl;
}

template <typename T>
uintptr_t convertAddressToInt(T *addPtr)
{
    return (uintptr_t)reinterpret_cast<void *>(addPtr);
}

template <typename T>
// only for non strings, i.e. float, double, int, char
void captureUserInput(string queryString, T &varToStore)
{
    printSimple(queryString);

    while (!(cin >> varToStore))
    {
        printSimple("Invalid input, please re-enter input: ");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    printWithArg("Input has been collected with value: ", varToStore);
}

void *allocateMemory(size_t objectSize, size_t objectAlign, Arena_Mem &arena)
{
    printSimple("========================ALLOCATE_MEMORY==========================");
    printWithArg("Object has size of", objectSize);
    printWithArg("Object has alignment of", objectAlign);
    uintptr_t currentPtr = convertAddressToInt(arena.current);
    uintptr_t delta;
    void *returnPtr;

    if (currentPtr % objectAlign != 0)
    {
        // not aligned, need to pad
        delta = objectAlign - (currentPtr % objectAlign);

        if ((currentPtr + objectSize + delta) > (convertAddressToInt(arena.start) + arena.mem_size))
        {
            printSimple("The block is too large and is out of bounds!");
            return nullptr;
        }
        else
        {
            arena.current = reinterpret_cast<char *>(currentPtr + delta);
            returnPtr = arena.current;
            printWithArg("Memory has been allocated and is within buffer founds with size: ", objectSize);
            printWithArg("The new current pointer is at and object is initialised here", currentPtr + delta);
            arena.current = reinterpret_cast<char *>(currentPtr + delta + objectSize);
            return returnPtr;
        }
    }
    else
    {
        if ((currentPtr + objectSize) > (convertAddressToInt(arena.start) + arena.mem_size))
        {
            printSimple("The block is too large and is out of bounds!");
            return nullptr;
        }
        // aligned can just use right away
        returnPtr = arena.current;
        printWithArg("Memory has been allocated and is within buffer found with size", objectSize);
        printWithArg("The object is initialised at", currentPtr);
        arena.current = reinterpret_cast<char *>(currentPtr + objectSize);

        return returnPtr;
    }
}

void resetArena(Arena_Mem &arena)
{
    printSimple("=================RESET_ARENA");
    arena.current = arena.start;
    printWithArg("Start of arena buffer is at", convertAddressToInt(arena.start));
    printWithArg("Arena has been reset, the current pointer is now at", convertAddressToInt(arena.current));
}

struct testObject
{
    double d;
    bool b;
    int i;
};

struct testObject2
{
    int i;
    char c;
    bool b;
};

int main()
{

    bool exit = false;
    size_t memorySpace;
    Arena_Mem arena;
    int userInput;

    captureUserInput("Please enter the size of the Arena: ", memorySpace);

    arena.start = reinterpret_cast<char *>(::operator new(memorySpace));
    arena.mem_size = memorySpace;
    arena.current = arena.start;

    printWithArg("You have allocated an Arena with size: ", arena.mem_size);
    printWithArg("The arena starts at : ", convertAddressToInt(arena.start));
    printWithArg("The arena ends at : ", convertAddressToInt(arena.start + arena.mem_size));

    while (!exit)
    {
        printSimple("Please select an option from the menu below.");
        printSimple("1. Allocate memory");
        printSimple("2. Clear memory");
        printSimple("9. Quit.");

        while (!(cin >> userInput) || (userInput < 1) || (userInput > 9))
        {
            printSimple("Invalid selection, please ensure your input is correct.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (userInput == 9)
        {
            exit = true;
        }
        else if (userInput == 1)
        {
            void *memPointer = allocateMemory(sizeof(testObject), alignof(testObject), arena);
            if (memPointer)
            {

                testObject *testObjectPtr = new (memPointer) testObject{7.5, false, 2};
                printWithArg("OBJECT IS AT ", convertAddressToInt(testObjectPtr));

                testObjectPtr->b = false;
                printWithArg("TESTING POINTER OF SET FIELD B", convertAddressToInt(&(testObjectPtr->b)));

                testObjectPtr->i = 2;
                printWithArg("TESTING POINTER OF SET FIELD I", convertAddressToInt(&(testObjectPtr->i)));
            }
            else
            {
                printSimple("ERROR WITH ALLOCATING MEMORY");
            }

            void *memPointer2 = allocateMemory(sizeof(testObject2), alignof(testObject2), arena);

            if (memPointer2)
            {
                testObject2 *testObjectPtr2 = new (memPointer2) testObject2{4, 'c', true};

                printWithArg("OBJECT IS AT ", convertAddressToInt(testObjectPtr2));
            }
            else
            {
                printSimple("ERROR WITH ALLOCATING MEMORY");
            }
        }
        else if (userInput == 2)
        {
            resetArena(arena);
        }
    }

    ::operator delete(arena.start);
    return 0;
}