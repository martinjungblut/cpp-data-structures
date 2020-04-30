#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "nodes.hpp"

template <typename T>
class Stack {
private:
  unsigned int count = 0;
  SinglyLinkedNode<T>* top;
  T defaultValue;

public:
  Stack<T> (T defaultValue) {
    this->top = NULL;
    this->defaultValue = defaultValue;
  }

  T push(T target) {
    this->count++;

    SinglyLinkedNode<T>* node = new SinglyLinkedNode<T>();
    node->data = target;
    if (top != NULL)
      node->reference = top;

    this->top = node;
    return this->top->data;
  }

  T pop() {
    if (this->top == NULL)
      return this->defaultValue;

    this->count--;
    T target = this->top->data;

    if (this->top->reference != NULL) {
      SinglyLinkedNode<T>* oldTop = this->top;
      this->top = top->reference;
      delete oldTop;
    } else {
      delete this->top;
      this->top = NULL;
    }

    return target;
  }

  T peek() {
    if (this->top != NULL)
      return this->top->data;
    else
      return this->defaultValue;
  }

  unsigned int size() {
    return this->count;
  }
};


TEST_CASE("stack - base usage", "stack") {
  Stack<int> stack(0);

  REQUIRE(stack.size() == 0);

  REQUIRE(stack.push(3) == 3);
  REQUIRE(stack.peek() == 3);
  REQUIRE(stack.size() == 1);

  REQUIRE(stack.push(-8) == -8);
  REQUIRE(stack.peek() == -8);
  REQUIRE(stack.size() == 2);

  REQUIRE(stack.push(12) == 12);
  REQUIRE(stack.peek() == 12);
  REQUIRE(stack.size() == 3);

  REQUIRE(stack.pop() == 12);
  REQUIRE(stack.peek() == -8);
  REQUIRE(stack.size() == 2);

  REQUIRE(stack.pop() == -8);
  REQUIRE(stack.peek() == 3);
  REQUIRE(stack.size() == 1);

  REQUIRE(stack.pop() == 3);
  REQUIRE(stack.peek() == 0);
  REQUIRE(stack.size() == 0);
}

TEST_CASE("stack - pop does not decrease size if there are no elements left", "stack") {
  Stack<int> stack(0);

  REQUIRE(stack.pop() == 0);
  REQUIRE(stack.size() == 0);

  REQUIRE(stack.pop() == 0);
  REQUIRE(stack.size() == 0);
}

TEST_CASE("stack - pop yields default element if there are no elements left", "stack") {
  Stack<int> stack(10);

  REQUIRE(stack.pop() == 10);

  stack.push(15);
  stack.push(20);
  REQUIRE(stack.pop() == 20);
  REQUIRE(stack.pop() == 15);

  REQUIRE(stack.pop() == 10);
  REQUIRE(stack.pop() == 10);
}
