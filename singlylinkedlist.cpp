#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

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

  unsigned int size() {
    return this->count;
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

  REQUIRE(list.size() == 4);
}