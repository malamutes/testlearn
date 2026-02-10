/*
Lesson 6 Objective:
Master smart pointers, RAII, and move semantics by building a doubly-linked list
with custom memory ownership. Learn move constructors, move assignment, and
automatic resource cleanup.

How to run from repo root:
  g++ -std=c++14 -Wall -Wextra -pedantic -I wrappers/ lessons/lesson-06/main.cpp
wrappers/wrappers.cpp -o lessons/lesson-06/main; lessons/lesson-06/main
*/

#include "wrappers.hpp"
#include <iostream>
#include <limits>
#include <memory>

// Node template for doubly-linked list
template <typename T> struct Node {
  T data;
  std::unique_ptr<Node<T>> next;
  Node<T> *prev;

  Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}
  Node(T &&value) : data(std::move(value)), next(nullptr), prev(nullptr) {}
};

// TODO: Implement a DoublyLinkedList<T> class with:
// 1) private members:
//    - std::unique_ptr<Node<T>> head
//    - Node<T>* tail (raw pointer is OK; owned by head)
//    - size_t size
//
// 2) public methods:
//    - Constructor (default, empty list)
//    - Destructor (automatic cleanup via unique_ptr RAII)
//    - push_back(const T& value) / push_back(T&& value) (move version)
//    - push_front(const T& value) / push_front(T&& value)
//    - pop_back() -> T (removes and returns last element)
//    - pop_front() -> T (removes and returns first element)
//    - T& front() / const T& front()
//    - T& back() / const T& back()
//    - size_t getSize() const
//    - bool isEmpty() const
//
// 3) Move semantics:
//    - Move constructor: DoublyLinkedList(DoublyLinkedList&& other)
//    - Move assignment: operator=(DoublyLinkedList&& other)
//    - Delete copy constructor and copy assignment (prevent shallow copies)
//
// 4) Iteration support (optional but recommended):
//    - Implement a simple printList() const for testing
//
// Requirements:
// - No raw new/delete in main(). All memory managed by std::unique_ptr.
// - Prevent memory leaks: use RAII (unique_ptr cleans up on destruction).
// - Implement move semantics to allow efficient list transfers.
// - Input validation for pop operations on empty list (throw
// std::out_of_range).
// - No global variables.

template <typename T> class DoublyLinkedList {
private:
  // TODO: Add private members here

public:
  // TODO: Implement constructors, destructor, and all methods
};

int main() {
  std::cout << "Lesson 6: Smart Pointers, RAII, and Move Semantics.\n";

  // TODO: Test your DoublyLinkedList implementation here.
  // Example ideas:
  // - Create a list, push elements
  // - Test move semantics (move list to another)
  // - Pop elements and print
  // - Verify automatic cleanup on scope exit
}