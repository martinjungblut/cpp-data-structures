#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "nodes.hpp"

template <typename T>
class DoublyLinkedList {
private:
  DoublyLinkedNode<T>* head;
  DoublyLinkedNode<T>* tail;
  unsigned int count;

public:
  DoublyLinkedList<T>() {
	this->head = NULL;
	this->tail = NULL;
	this->count = 0;
  }

  unsigned int size() {
	return this->count;
  }

  int index(T element) {
    DoublyLinkedNode<T>* current = this->head;
    int index = 0;

    while (current != NULL) {
      if (current->data == element)
		return index;

      current = current->next;
      index++;
    }

    return -1;
  }

  void display(std::string message) {
    DoublyLinkedNode<T>* node = this->head;

	std::cout << "Message:" << message << std::endl;

	if (this->head != NULL)
	  std::cout << "Head: " << *this->head << std::endl;

	while (node != NULL) {
	  std::cout << "Node: " << *node << std::endl;
	  if (node->next == node) {
		std::cout << "Cyclic reference found!" << std::endl;
		break;
	  } else {
		node = node->next;
	  }
	}

	if (this->tail != NULL)
	  std::cout << "Tail: " << *this->tail << std::endl;

	std::cout << "" << std::endl;
  }

  T access(int targetIndex) {
    DoublyLinkedNode<T>* current = this->head;
    int index = 0;

    while (current != NULL) {
	  if (index == targetIndex)
		return current->data;

      current = current->next;
      index++;
    }

    throw new std::out_of_range("Index out of range.");
  }

  T append(T element) {
    DoublyLinkedNode<T>* node = new DoublyLinkedNode<T>();
    node->data = element;
	node->previous = this->tail;

    if (this->head == NULL) {
      this->head = node;
	}

    if (this->tail != NULL) {
      this->tail->next = node;
	}
    this->tail = node;

    this->count++;
    return node->data;
  }

  T prepend(T element) {
    DoublyLinkedNode<T>* node = new DoublyLinkedNode<T>();
    node->data = element;
	node->next = this->head;

	if (this->head != NULL) {
	  this->head->previous = node;
	}
	this->head = node;

	if (this->tail == NULL) {
	  this->tail = node;
	}

	this->count++;
	return node->data;
  }

  T pop(int targetIndex) {
    DoublyLinkedNode<T>* current = this->head;
    int index = 0;

    while (current != NULL) {
      if (index == targetIndex) { 
		if (current == this->head) {
		  if (this->head == this->tail)
			this->tail = this->tail->next;

		  this->head = this->head->next;

		  if (this->head != NULL)
			this->head->previous = NULL;
		} else if (current == this->tail) {
		  this->tail = this->tail->previous;

		  if (this->tail != NULL)
			this->tail->next = NULL;
		} else {
		  current->previous->next = current->next;
		  current->next->previous = current->previous;
		}

		T element = current->data;
		delete current;
		this->count--;
		return element;
      } else {
		current = current->next;
		index++;
      }
	}

    throw new std::out_of_range("Index out of range.");
  }

};

TEST_CASE("doubly linked list - size / index / append", "doublylinkedlist") {
  DoublyLinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.index(1) == -1);
  REQUIRE(list.index(2) == -1);

  REQUIRE(list.append(1) == 1);
  REQUIRE(list.size() == 1);
  REQUIRE(list.append(2) == 2);
  REQUIRE(list.size() == 2);

  REQUIRE(list.index(1) == 0);
  REQUIRE(list.index(2) == 1);
}

TEST_CASE("doubly linked list - prepend and append", "doublylinkedlist") {
  DoublyLinkedList<int> list;

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

TEST_CASE("doubly linked list - index returns index of first occurrence", "doublylinkedlist") {
  DoublyLinkedList<int> list;

  list.append(10);
  list.append(10);

  REQUIRE(list.index(10) == 0);
}

TEST_CASE("singly linked list - access", "singlylinkedlist") {
  DoublyLinkedList<int> list;

  REQUIRE_THROWS_AS(list.access(0), std::out_of_range*);
  REQUIRE_THROWS_AS(list.access(1), std::out_of_range*);

  list.append(1);
  REQUIRE(list.access(0) == 1);

  list.append(2);
  REQUIRE(list.access(1) == 2);
}

TEST_CASE("doubly linked list - pop", "doublylinkedlist") {
  DoublyLinkedList<int> list;

  // throw exceptions if empty
  REQUIRE_THROWS_AS(list.pop(0), std::out_of_range*);
  REQUIRE_THROWS_AS(list.pop(1), std::out_of_range*);
  REQUIRE_THROWS_AS(list.pop(2), std::out_of_range*);

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

  // pop from middle, then tail, then tail, then head
  list.append(10);
  list.append(20);
  list.append(30);
  list.append(40);
  REQUIRE(list.pop(1) == 20);
  REQUIRE(list.size() == 3);
  REQUIRE(list.index(20) == -1);
  REQUIRE(list.index(10) == 0);
  REQUIRE(list.index(30) == 1);
  REQUIRE(list.index(40) == 2);

  REQUIRE(list.pop(2) == 40);
  REQUIRE(list.size() == 2);
  REQUIRE(list.index(40) == -1);
  REQUIRE(list.index(10) == 0);
  REQUIRE(list.index(30) == 1);

  REQUIRE(list.pop(1) == 30);
  REQUIRE(list.size() == 1);
  REQUIRE(list.index(30) == -1);
  REQUIRE(list.index(10) == 0);

  REQUIRE(list.pop(0) == 10);
  REQUIRE(list.size() == 0);
  REQUIRE(list.index(10) == -1);

  // pop non-existing element from list with 1, 2 and 3 elements
  REQUIRE(list.size() == 0);

  list.append(1);
  REQUIRE_THROWS_AS(list.pop(10), std::out_of_range*);
  REQUIRE(list.size() == 1);

  list.append(2);
  REQUIRE_THROWS_AS(list.pop(10), std::out_of_range*);
  REQUIRE(list.size() == 2);

  list.append(3);
  REQUIRE_THROWS_AS(list.pop(10), std::out_of_range*);
  REQUIRE(list.size() == 3);
}
