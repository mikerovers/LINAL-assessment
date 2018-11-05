#include <catch.hpp>
#include "../src/Vector.h"

TEST_CASE("basic vector math", "[vector]") {
    GIVEN("a default vector") {
        // Addition.

        Vector v(0, 0);

        REQUIRE(v.getY() == 0);
        REQUIRE(v.getX() == 0);

        Vector v2(5, 7);
        v + v2;

        REQUIRE(v.getX() == 5);
        REQUIRE(v.getY() == 7);

        // Subtraction.

        Vector v3(2, 6);
        v - v3;

        REQUIRE(v.getX() == 3);
        REQUIRE(v.getY() == 1);

        // Multiply.
        Vector v4(5, 3);

        v4 * 3;

        REQUIRE(v4.getX() == 15);
        REQUIRE(v4.getY() == 9);

        // Length.
        Vector v5(3, 4);

        REQUIRE(v5.length() == 5);

        // Normalize
        Vector v6(3, 4);

        REQUIRE(v6.length() == 5);
        v6.normalize();
        REQUIRE(v6.getX() == 0.6);
        REQUIRE(v6.getY() == 0.8);
        REQUIRE(v6.length() == 1);
    }
}