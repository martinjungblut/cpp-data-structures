#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "nodes.hpp"

TEST_CASE("SinglyLinkedNodeHooks", "reset") {
  SinglyLinkedNodeHooks::reset();
  REQUIRE(SinglyLinkedNodeHooks::onNew == nullptr);
  REQUIRE(SinglyLinkedNodeHooks::onDelete == nullptr);

  SinglyLinkedNodeHooks::onNew = [](){};
  SinglyLinkedNodeHooks::onDelete = [](){};
  REQUIRE(SinglyLinkedNodeHooks::onNew != nullptr);
  REQUIRE(SinglyLinkedNodeHooks::onDelete != nullptr);

  SinglyLinkedNodeHooks::reset();
  REQUIRE(SinglyLinkedNodeHooks::onNew == nullptr);
  REQUIRE(SinglyLinkedNodeHooks::onDelete == nullptr);
}

TEST_CASE("SinglyLinkedNode", "new and delete") {
  unsigned int newCalled = 0;
  unsigned int deleteCalled = 0;

  SinglyLinkedNodeHooks::onNew = [&]() { newCalled++; };
  SinglyLinkedNodeHooks::onDelete = [&]() { deleteCalled++; };

  REQUIRE(newCalled == 0);
  SinglyLinkedNode<int>* intNode = new SinglyLinkedNode<int>();
  REQUIRE(newCalled == 1);
  SinglyLinkedNode<bool>* boolNode = new SinglyLinkedNode<bool>();
  REQUIRE(newCalled == 2);

  REQUIRE(deleteCalled == 0);
  delete intNode;
  REQUIRE(deleteCalled == 1);
  delete boolNode;
  REQUIRE(deleteCalled == 2);
}

TEST_CASE("DoublyLinkedNodeHooks", "reset") {
  DoublyLinkedNodeHooks::reset();
  REQUIRE(DoublyLinkedNodeHooks::onNew == nullptr);
  REQUIRE(DoublyLinkedNodeHooks::onDelete == nullptr);

  DoublyLinkedNodeHooks::onNew = [](){};
  DoublyLinkedNodeHooks::onDelete = [](){};
  REQUIRE(DoublyLinkedNodeHooks::onNew != nullptr);
  REQUIRE(DoublyLinkedNodeHooks::onDelete != nullptr);

  DoublyLinkedNodeHooks::reset();
  REQUIRE(DoublyLinkedNodeHooks::onNew == nullptr);
  REQUIRE(DoublyLinkedNodeHooks::onDelete == nullptr);
}

TEST_CASE("DoublyLinkedNode", "new and delete") {
  unsigned int newCalled = 0;
  unsigned int deleteCalled = 0;

  DoublyLinkedNodeHooks::onNew = [&]() { newCalled++; };
  DoublyLinkedNodeHooks::onDelete = [&]() { deleteCalled++; };

  REQUIRE(newCalled == 0);
  DoublyLinkedNode<int>* intNode = new DoublyLinkedNode<int>();
  REQUIRE(newCalled == 1);
  DoublyLinkedNode<bool>* boolNode = new DoublyLinkedNode<bool>();
  REQUIRE(newCalled == 2);

  REQUIRE(deleteCalled == 0);
  delete intNode;
  REQUIRE(deleteCalled == 1);
  delete boolNode;
  REQUIRE(deleteCalled == 2);
}
