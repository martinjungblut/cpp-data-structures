#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "trackers.hpp"

TEST_CASE("DeallocationTracker", "trackers") {
  DeallocationTracker* ptracker = new DeallocationTracker();
  bool* ref = ptracker->getReference();

  REQUIRE(*ref == false);
  delete ptracker;
  REQUIRE(*ref == true);
  delete ref;
}
