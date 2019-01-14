#include <catch.hpp>
#include "../src/Vector2D.h"
#include "../src/Vector3D.h"

TEST_CASE("basic vector math", "[vector3d]") {
    Vector3D v(1, 4, 6);

    REQUIRE(v.getX() == 1);
    REQUIRE(v.getY() == 4);
    REQUIRE(v.getZ() == 6);

    // Addition.
    Vector3D v2(5, 7, 3);
    v + v2;

    REQUIRE(v.getX() == 6);
    REQUIRE(v.getY() == 11);
    REQUIRE(v.getZ() == 9);

    // Subtraction.
    Vector3D v3(4, 2, -12);
    Vector3D v4(2, 6, 3);
    v3 - v4;

    REQUIRE(v3.getX() == 2);
    REQUIRE(v3.getY() == -4);
    REQUIRE(v3.getZ() == -15);

    // Multiply.
    Vector3D v5(5, 3, 4);

    v5 * 3;

    REQUIRE(v5.getX() == 15);
    REQUIRE(v5.getY() == 9);
    REQUIRE(v5.getZ() == 12);

    // Length.
    Vector3D v6(3, 4, 0);

    REQUIRE(v6.length() == 5);

    // Normalize
    Vector3D v7(3, 4, 0);

    REQUIRE(v7.length() == 5);
    auto v8 = v7.normalize();
    REQUIRE(v8.getX() == 0.6);
    REQUIRE(v8.getY() == 0.8);
    REQUIRE(v8.length() == 1);
}

TEST_CASE("advanced vector tests", "[vector3d]") {
    // Distance
    Vector3D v1(1, 0, 5);
    Vector3D v2(0, 2, 4);

    REQUIRE(v1.distance(v2) == std::sqrt(6));

    // Cross product
    Vector3D v3{1, 0, 0};
    Vector3D v4{0, 1, 0};

    auto v5 = v3.crossProduct(v4);
    REQUIRE(v5.getX() == 0);
    REQUIRE(v5.getY() == 0);
    REQUIRE(v5.getZ() == 1);

    // Cross product, same direction
    Vector3D v6{1, 0, 0};
    Vector3D v7{-1, 0, 0};

    auto v8 = v6.crossProduct(v7);
    REQUIRE(v8.getX() == 0);
    REQUIRE(v8.getY() == 0);
    REQUIRE(v8.getZ() == 0);

    // Dot product
    Vector3D v9{2, 4, 1};
    Vector3D v10{4, 1, 1};

    auto in1 = v9.inProduct(v10);
    REQUIRE(in1 == 13);

    // Angle
    Vector3D v12{2, 4, 0};
    Vector3D v13{3, 2, 0};

    REQUIRE(std::round(v12.angle(v13)) == 50);

    // Another cross product
    Vector3D v14{77, 2, -11};
    Vector3D v15{77, -7, 11};

    auto v16 = v14.crossProduct(v15);
    REQUIRE(v16.getX() == -55);
    REQUIRE(v16.getY() == -1694);
    REQUIRE(v16.getZ() == -693);
}