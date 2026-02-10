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

  // Move constructor: takes ownership of next's resources
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
//    - Implement a simple forward iterator or just add:
//      void printList() const (for testing)
//
// Requirements:
// - No raw new/delete in main(). All memory managed by std::unique_ptr.
// - Prevent memory leaks: use RAII (unique_ptr cleans up on destruction).
// - Implement move semantics to allow efficient list transfers.
// - Input validation for pop operations on empty list.
// - No global variables.
//
// Example usage (after implementation):
//   DoublyLinkedList<int> list;
//   list.push_back(10);
//   list.push_back(20);
//   std::cout << list.front() << std::endl;  // 10
//   int val = list.pop_front();              // 10
//   DoublyLinkedList<int> list2 = std::move(list);  // Move, not copy

template <typename T> class DoublyLinkedList {
private:
  std::unique_ptr<Node<T>> head;
  Node<T> *tail;
  size_t size;

public:
  DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

  // Delete copy constructor and copy assignment (prevent shallow copies)
  DoublyLinkedList(const DoublyLinkedList &other) = delete;
  DoublyLinkedList &operator=(const DoublyLinkedList &other) = delete;

  // Move constructor
  DoublyLinkedList(DoublyLinkedList &&other) noexcept
      : head(std::move(other.head)), tail(other.tail), size(other.size) {
    other.tail = nullptr;
    other.size = 0;
  }

  // Move assignment operator
  DoublyLinkedList &operator=(DoublyLinkedList &&other) noexcept {
    if (this != &other) {
      head = std::move(other.head);
      tail = other.tail;
      size = other.size;
      other.tail = nullptr;
      other.size = 0;
    }
    return *this;
  }

  ~DoublyLinkedList() = default; // unique_ptr handles cleanup

  // Push to back (lvalue reference)
  void push_back(const T &value) {
    auto newNode = std::make_unique<Node<T>>(value);
    Node<T> *rawPtr = newNode.get();

    if (!head) {
      head = std::move(newNode);
      tail = rawPtr;
    } else {
      rawPtr->prev = tail;
      tail->next = std::move(newNode);
      tail = rawPtr;
    }
    size++;
  }

  // Push to back (rvalue reference - move)
  void push_back(T &&value) {
    auto newNode = std::make_unique<Node<T>>(std::move(value));
    Node<T> *rawPtr = newNode.get();

    if (!head) {
      head = std::move(newNode);
      tail = rawPtr;
    } else {
      rawPtr->prev = tail;
      tail->next = std::move(newNode);
      tail = rawPtr;
    }
    size++;
  }

  // Push to front (lvalue reference)
  void push_front(const T &value) {
    auto newNode = std::make_unique<Node<T>>(value);
    Node<T> *rawPtr = newNode.get();

    if (!head) {
      head = std::move(newNode);
      tail = rawPtr;
    } else {
      newNode->next = std::move(head);
      newNode->next->prev = rawPtr;
      head = std::move(newNode);
    }
    size++;
  }

  // Push to front (rvalue reference - move)
  void push_front(T &&value) {
    auto newNode = std::make_unique<Node<T>>(std::move(value));
    Node<T> *rawPtr = newNode.get();

    if (!head) {
      head = std::move(newNode);
      tail = rawPtr;
    } else {
      newNode->next = std::move(head);
      newNode->next->prev = rawPtr;
      head = std::move(newNode);
    }
    size++;
  }

  // Pop from back
  T pop_back() {
    if (!tail) {
      throw std::out_of_range("pop_back() called on empty list");
    }

    T value = std::move(tail->data);

    if (tail->prev) {
      tail = tail->prev;
      tail->next = nullptr;
    } else {
      head = nullptr;
      tail = nullptr;
    }
    size--;
    return value;
  }

  // Pop from front
  T pop_front() {
    if (!head) {
      throw std::out_of_range("pop_front() called on empty list");
    }

    T value = std::move(head->data);
    head = std::move(head->next);

    if (head) {
      head->prev = nullptr;
    } else {
      tail = nullptr;
    }
    size--;
    return value;
  }

  T &front() {
    if (!head) {
      throw std::out_of_range("front() called on empty list");
    }
    return head->data;
  }

  const T &front() const {
    if (!head) {
      throw std::out_of_range("front() called on empty list");
    }
    return head->data;
  }

  T &back() {
    if (!tail) {
      throw std::out_of_range("back() called on empty list");
    }
    return tail->data;
  }

  const T &back() const {
    if (!tail) {
      throw std::out_of_range("back() called on empty list");
    }
    return tail->data;
  }

  size_t getSize() const { return size; }

  bool isEmpty() const { return size == 0; }

  void printList() const {
    std::cout << "List (size " << size << "): [";
    Node<T> *current = head.get();
    while (current) {
      std::cout << current->data;
      if (current->next) {
        std::cout << " <-> ";
      }
      current = current->next.get();
    }
    std::cout << "]\n";
  }
};

int main() {
  std::cout << "Lesson 6: Smart Pointers, RAII, and Move Semantics.\n\n";

  // Example: Create a list, push elements, demonstrate move semantics
  DoublyLinkedList<int> list1;
  list1.push_back(10);
  list1.push_back(20);
  list1.push_back(30);
  std::cout << "list1: ";
  list1.printList();
  std::cout << "Front: " << list1.front() << ", Back: " << list1.back()
            << "\n\n";

  // Move list1 to list2 (transfer ownership)
  DoublyLinkedList<int> list2 = std::move(list1);
  std::cout << "After move: list1 is now empty.\n";
  std::cout << "list1 size: " << list1.getSize() << "\n";
  std::cout << "list2: ";
  list2.printList();
  std::cout << "\n";

  // Pop operations
  int val = list2.pop_front();
  std::cout << "Popped from front: " << val << "\n";
  std::cout << "list2: ";
  list2.printList();

  val = list2.pop_back();
  std::cout << "Popped from back: " << val << "\n";
  std::cout << "list2: ";
  list2.printList();

  std::cout << "\nLesson 6 complete. All memory cleaned up automatically via "
               "RAII.\n";
  return 0;
}
