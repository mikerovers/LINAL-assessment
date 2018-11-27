#include <catch.hpp>
#include "../src/Vector2D.h"
#include "../src/Matrix2D.h"

TEST_CASE("basic matrix math", "[matrix]") {
    GIVEN("a default matrix") {
        // Translation
        auto m1 = Matrix2D{1};
        m1(0, 0) = 2;
        m1(1, 0) = 3;
        m1(2, 0) = 1;

        m1.translate(1, 2);
        REQUIRE(m1(0, 0) == 3);
        REQUIRE(m1(1, 0) == 5);

    }
}