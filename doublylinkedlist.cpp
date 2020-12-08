#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <functional>
#include "nodes.hpp"

template <typename T>
class DoublyLinkedList {
private:
  DoublyLinkedNode<T>* head;
  DoublyLinkedNode<T>* tail;
  unsigned int count;

  bool iterate(std::function<bool(unsigned int, DoublyLinkedNode<T>*, unsigned int, DoublyLinkedNode<T>*)> action) {
    DoublyLinkedNode<T> *lnode = this->head, *rnode = this->tail;
    unsigned int ilnode = 0, irnode = this->size() - 1;

    while (lnode != NULL && rnode != NULL) {
      if (action(ilnode, lnode, irnode, rnode))
        return true;

      if (lnode == rnode) {
        break;
      } else {
        lnode = lnode->next, ilnode++;
        rnode = rnode->previous, irnode--;
      }
    }

    return false;
  }

public:
  DoublyLinkedList<T>() {
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
  }

  ~DoublyLinkedList<T>() {
    for (int i = this->size() - 1; i >= 0; i--) {
      this->pop(i);
    }
  }

  unsigned int size() {
    return this->count;
  }

  int index(T element) {
    unsigned int index = 0;

    bool assigned = this->iterate([&index, element](unsigned int ia, DoublyLinkedNode<T>* a, unsigned int ib, DoublyLinkedNode<T>* b) {
      if (a->data == element) {
        index = ia;
        return true;
      } else if (b->data == element) {
        index = ib;
        return true;
      } else {
        return false;
      }
    });

    if (assigned)
      return index;
    else
      return -1;
  }

  T access(unsigned int index) {
    T result;

    bool assigned = this->iterate([index, &result](unsigned int ia, DoublyLinkedNode<T>* a, unsigned int ib, DoublyLinkedNode<T>* b) {
      if (ia == index) {
        result = a->data;
        return true;
      } else if (ib == index) {
        result = b->data;
        return true;
      } else {
        return false;
      }
    });

    if (assigned)
      return result;
    else
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

  T pop(unsigned int targetIndex) {
    DoublyLinkedNode<T>* target = NULL;

    bool found = this->iterate([targetIndex, &target](unsigned int ia, DoublyLinkedNode<T>* a, unsigned int ib, DoublyLinkedNode<T>* b) {
      if (ia == targetIndex) {
        target = a;
        return true;
      } else if (ib == targetIndex) {
        target = b;
        return true;
      } else {
        return false;
      }
    });

    if (found) {
      if (this->size() == 1) {
        this->head = NULL, this->tail = NULL;
      } else if (target == this->head) {
        this->head = this->head->next;
        this->head->previous = NULL;
      } else if (target == this->tail) {
        this->tail = this->tail->previous;
        this->tail->next = NULL;
      } else {
        target->previous->next = target->next;
        target->next->previous = target->previous;
      }

      T data = target->data;
      delete target;
      this->count--;
      return data;
    } else {
      throw new std::out_of_range("Index out of range.");
    }
  }
};

TEST_CASE("common operations", "[doublylinkedlist]") {
  DoublyLinkedList<int> list;

  SECTION("size / index/ append") {
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

  SECTION("prepend / append") {
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

  SECTION("index returns index of first occurrence") {
    list.append(10);
    list.append(10);

    REQUIRE(list.index(10) == 0);
  }

  SECTION("access") {
    REQUIRE_THROWS_AS(list.access(0), std::out_of_range*);
    REQUIRE_THROWS_AS(list.access(1), std::out_of_range*);

    list.append(1);
    REQUIRE(list.access(0) == 1);

    list.append(2);
    REQUIRE(list.access(1) == 2);
  }

  SECTION("pop") {
    SECTION("throw exceptions if empty") {
      REQUIRE_THROWS_AS(list.pop(0), std::out_of_range*);
      REQUIRE_THROWS_AS(list.pop(1), std::out_of_range*);
      REQUIRE_THROWS_AS(list.pop(2), std::out_of_range*);
    }

    SECTION("from head") {
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
    }

    SECTION("from tail") {
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
    }

    SECTION("from middle, then tail, then head") {
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

    SECTION("from middle, then tail, then tail, then head") {
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
    }

    SECTION("non-existing element from list with 1, 2 and 3 elements") {
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
  }
}

TEST_CASE("memory allocation", "[doublylinkedlist]") {
  unsigned int newCalled = 0, deleteCalled = 0;
  DoublyLinkedNodeHooks::onNew = [&]() { newCalled++; };
  DoublyLinkedNodeHooks::onDelete = [&]() { deleteCalled++; };
  REQUIRE(newCalled == 0);
  REQUIRE(deleteCalled == 0);

  SECTION("heap allocated") {
    DoublyLinkedList<int>* list = new DoublyLinkedList<int>();

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

  SECTION("stack allocated") {
    std::function<void()> callable = [&newCalled, &deleteCalled]() {
      DoublyLinkedList<int> list = DoublyLinkedList<int>();

      list.append(30);
      list.append(40);
      list.append(50);
      REQUIRE(newCalled == 3);
      REQUIRE(deleteCalled == 0);

      list.prepend(20);
      list.prepend(10);
      REQUIRE(newCalled == 5);
      REQUIRE(deleteCalled == 0);

      list.index(10);
      list.access(0);
      REQUIRE(newCalled == 5);
      REQUIRE(deleteCalled == 0);

      // pop from middle: [10 20 30 40 50] -> [10 20 40 50]
      list.pop(2);
      REQUIRE(newCalled == 5);
      REQUIRE(deleteCalled == 1);

      // pop from head: [10 30 40 50] -> [30 40 50]
      list.pop(0);
      REQUIRE(newCalled == 5);
      REQUIRE(deleteCalled == 2);

      // pop from tail: [30 40 50] -> [30 40]
      list.pop(2);
      REQUIRE(newCalled == 5);
      REQUIRE(deleteCalled == 3);
    };

    callable();
    REQUIRE(newCalled == 5);
    REQUIRE(deleteCalled == 5);
  }
}
