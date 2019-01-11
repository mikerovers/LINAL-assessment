#include <catch.hpp>
#include "../src/Vector2D.h"
#include "../src/Vector3D.h"

TEST_CASE("basic vector math", "[vector]") {
    GIVEN("a default vector") {
        // Addition.

        Vector2D v(0, 0);

        REQUIRE(v.getY() == 0);
        REQUIRE(v.getX() == 0);

        Vector2D v2(5, 7);
        v + v2;

        REQUIRE(v.getX() == 5);
        REQUIRE(v.getY() == 7);

        // Subtraction.

        Vector2D v3(2, 6);
        v - v3;

        REQUIRE(v.getX() == 3);
        REQUIRE(v.getY() == 1);

        // Multiply.
        Vector2D v4(5, 3);

        v4 * 3;

        REQUIRE(v4.getX() == 15);
        REQUIRE(v4.getY() == 9);

        // Length.
        Vector2D v5(3, 4);

        REQUIRE(v5.length() == 5);

        // Normalize
        Vector2D v6(3, 4);

        REQUIRE(v6.length() == 5);
        v6.normalize();
        REQUIRE(v6.getX() == 0.6);
        REQUIRE(v6.getY() == 0.8);
        REQUIRE(v6.length() == 1);

        Vector2D v7(2, 4);
        Vector2D v8(2, 5);
        Vector2D v9(2, 4);

        REQUIRE(v7 != v8);
        REQUIRE(v7 == v9);
    }
}

TEST_CASE("vector3d tests", "[vector3d]") {
    Vector3D v10(1, 0, 5);
    Vector3D v11(0, 2, 4);

    REQUIRE(v10.distance(v11) == std::sqrt(6));
}