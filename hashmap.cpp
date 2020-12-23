#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#import <iostream>

class Hashable {
public:
  virtual std::size_t hash() = 0;
};

class HashableInt {
private:
  int value;

public:
  HashableInt(int value) {
    this->value = value;
  }

  virtual std::size_t hash() {
    return this->value;
  }
};

template <typename K, typename V>
class Hashmap {
private:
  V* array;
  std::size_t capacity;

public:
  Hashmap<K, V>() {
    this->capacity = 5;
    this->array = new V[5];

    for (size_t i = 0; i < this->capacity; i++)
      this->array[i] = V();
  }

  ~Hashmap<K, V>() {
    delete[] this->array;
  }

  void set(K key, V value) {
    std::size_t index = key.hash() % this->capacity;
    this->array[index] = value;
  }

  V get(K key) {
    std::size_t index = key.hash() % this->capacity;

    if (this->array[index] == V())
      throw new std::out_of_range("Index out of range.");
    else
      return this->array[index];
  }
};

TEST_CASE("common operations", "[hashmap]") {
  Hashmap<HashableInt, std::string> map;

  SECTION("set()") {
    map.set(1, "john mccarthy");
    REQUIRE(map.get(1) == "john mccarthy");

    map.set(2, "james gosling");
    REQUIRE(map.get(2) == "james gosling");
  }

  SECTION("get() non-existing key should raise an exception") {
    REQUIRE_THROWS_AS(map.get(0), std::out_of_range*);
  }

  SECTION("ensure empty values are respected for built-in types") {
    Hashmap<HashableInt, int> imap;
    REQUIRE_THROWS_AS(imap.get(0), std::out_of_range*);

    Hashmap<HashableInt, bool> bmap;
    REQUIRE_THROWS_AS(bmap.get(0), std::out_of_range*);
  }
}
