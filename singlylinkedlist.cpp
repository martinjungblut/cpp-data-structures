#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <stdexcept>
#include "nodes.hpp"

template <typename T>
class SinglyLinkedList {
private:
  unsigned int count = 0;
  SinglyLinkedNode<T>* head;
  SinglyLinkedNode<T>* tail;

public:
  SinglyLinkedList<T>() {
    this->head = NULL;
    this->tail = NULL;
  }

  ~SinglyLinkedList<T>() {
    for (int i = this->count - 1; i >= 0; i--) {
      this->pop(i);
    }
  }

  unsigned int size() {
    return this->count;
  }

  T pop(int targetIndex) {
    SinglyLinkedNode<T>* current = this->head;
    SinglyLinkedNode<T>* previous = this->head;
    int index = 0;

    while (current != NULL)
      if (index == targetIndex) {
        if (current == this->head) {
          this->head = current->reference;
        } else if (current == this->tail) {
          this->tail = previous;
          this->tail->reference = NULL;
        } else {
          previous->reference = current->reference;
        }

        T element = current->data;
        delete current;
        this->count--;
        return element;
      } else {
        previous = current;
        current = current->reference;
        index++;
      }

    throw new std::out_of_range("Index out of range.");
  }

  T access(int targetIndex) {
    SinglyLinkedNode<T>* current = this->head;
    int index = 0;

    while (current != NULL) {
      if (index == targetIndex)
        return current->data;

      current = current->reference;
      index++;
    }

    throw new std::out_of_range("Index out of range.");
  }

  int index(T element) {
    SinglyLinkedNode<T>* current = this->head;
    int index = 0;

    while (current != NULL) {
      if (current->data == element)
        return index;

      current = current->reference;
      index++;
    }

    return -1;
  }

  T append(T element) {
    SinglyLinkedNode<T>* node = new SinglyLinkedNode<T>();
    node->data = element;

    if (this->tail != NULL)
      this->tail->reference = node;

    this->tail = node;

    if (this->head == NULL)
      this->head = node;

    this->count++;
    return node->data;
  }

  T prepend(T element) {
    SinglyLinkedNode<T>* node = new SinglyLinkedNode<T>();
    node->data = element;
    node->reference = this->head;

    this->head = node;

    if (this->tail == NULL)
      this->tail = node;

    this->count++;
    return node->data;
  }
};

TEST_CASE("singly linked list - size / index / append", "singlylinkedlist") {
  SinglyLinkedList<int> list;

  REQUIRE(list.size() == 0);

  REQUIRE(list.index(1) == -1);
  REQUIRE(list.append(1) == 1);
  REQUIRE(list.size() == 1);
  REQUIRE(list.index(1) == 0);

  REQUIRE(list.index(2) == -1);
  REQUIRE(list.append(2) == 2);
  REQUIRE(list.size() == 2);
  REQUIRE(list.index(2) == 1);
}

TEST_CASE("singly linked list - prepend and append work consistently", "singlylinkedlist") {
  SinglyLinkedList<int> list;

  REQUIRE(list.prepend(10) == 10);
  REQUIRE(list.index(10) == 0);

  REQUIRE(list.append(20) == 20);
  REQUIRE(list.index(10) == 0);
  REQUIRE(list.index(20) == 1);

  REQUIRE(list.prepend(30) == 30);
  REQUIRE(list.index(30) == 0);
  REQUIRE(list.index(10) == 1);
  REQUIRE(list.index(20) == 2);

  REQUIRE(list.append(40) == 40);
  REQUIRE(list.index(30) == 0);
  REQUIRE(list.index(10) == 1);
  REQUIRE(list.index(20) == 2);
  REQUIRE(list.index(40) == 3);
}

TEST_CASE("singly linked list - index returns index of first occurrence", "singlylinkedlist") {
  SinglyLinkedList<int> list;

  list.append(10);
  list.append(10);

  REQUIRE(list.index(10) == 0);
}

TEST_CASE("singly linked list - access", "singlylinkedlist") {
  SinglyLinkedList<int> list;

  REQUIRE_THROWS_AS(list.access(0), std::out_of_range*);
  REQUIRE_THROWS_AS(list.access(1), std::out_of_range*);

  list.append(1);
  REQUIRE(list.access(0) == 1);

  list.append(2);
  REQUIRE(list.access(1) == 2);
}

TEST_CASE("singly linked list - pop", "singlylinkedlist") {
  SinglyLinkedList<int> list;

  // throw exceptions if empty
  REQUIRE_THROWS_AS(list.pop(0), std::out_of_range*);
  REQUIRE_THROWS_AS(list.pop(1), std::out_of_range*);

  // pop from head
  list.append(10);
  list.append(20);
  list.append(30);
  REQUIRE(list.pop(0) == 10);
  REQUIRE(list.size() == 2);
  REQUIRE(list.index(10) == -1);

  REQUIRE(list.pop(0) == 20);
  REQUIRE(list.size() == 1);
  REQUIRE(list.index(20) == -1);

  REQUIRE(list.pop(0) == 30);
  REQUIRE(list.size() == 0);
  REQUIRE(list.index(30) == -1);

  // pop from tail
  list.append(10);
  list.append(20);
  list.append(30);
  REQUIRE(list.pop(2) == 30);
  REQUIRE(list.size() == 2);
  REQUIRE(list.index(30) == -1);

  REQUIRE(list.pop(1) == 20);
  REQUIRE(list.size() == 1);
  REQUIRE(list.index(30) == -1);

  REQUIRE(list.pop(0) == 10);
  REQUIRE(list.size() == 0);
  REQUIRE(list.index(30) == -1);

  // pop from middle, then tail, then head
  list.append(10);
  list.append(20);
  list.append(30);
  REQUIRE(list.pop(1) == 20);
  REQUIRE(list.size() == 2);
  REQUIRE(list.index(20) == -1);
  REQUIRE(list.index(10) == 0);
  REQUIRE(list.index(30) == 1);

  REQUIRE(list.pop(1) == 30);
  REQUIRE(list.size() == 1);
  REQUIRE(list.index(30) == -1);
  REQUIRE(list.index(10) == 0);

  REQUIRE(list.pop(0) == 10);
  REQUIRE(list.size() == 0);
  REQUIRE(list.index(10) == -1);
}

TEST_CASE("singly linked list - memory allocation", "singlylinkedlist") {
  unsigned int newCalled = 0;
  unsigned int deleteCalled = 0;

  SinglyLinkedNodeHooks::onNew = [&]() { newCalled++; };
  SinglyLinkedNodeHooks::onDelete = [&]() { deleteCalled++; };

  SinglyLinkedList<int>* list = new SinglyLinkedList<int>();
  REQUIRE(newCalled == 0);
  REQUIRE(deleteCalled == 0);

  list->append(30);
  list->append(40);
  list->append(50);
  REQUIRE(newCalled == 3);
  REQUIRE(deleteCalled == 0);

  list->prepend(20);
  list->prepend(10);
  REQUIRE(newCalled == 5);
  REQUIRE(deleteCalled == 0);

  list->index(10);
  list->access(0);
  REQUIRE(newCalled == 5);
  REQUIRE(deleteCalled == 0);

  // pop from middle: [10 20 30 40 50] -> [10 20 40 50]
  list->pop(2);
  REQUIRE(newCalled == 5);
  REQUIRE(deleteCalled == 1);

  // pop from head: [10 30 40 50] -> [30 40 50]
  list->pop(0);
  REQUIRE(newCalled == 5);
  REQUIRE(deleteCalled == 2);

  // pop from tail: [30 40 50] -> [30 40]
  list->pop(2);
  REQUIRE(newCalled == 5);
  REQUIRE(deleteCalled == 3);

  delete list;
  REQUIRE(newCalled == 5);
  REQUIRE(deleteCalled == 5);
}
