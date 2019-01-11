#include <catch.hpp>
#include "../src/Vector2D.h"
#include "../src/Matrix.h"
#include "../src/MyMesh.h"

TEST_CASE("basic matrix math", "[matrix]") {
    GIVEN("default") {
        auto s = Matrix::ScalingMatrix(2, 3, 4);
        REQUIRE(s(0, 0) == 2);
        REQUIRE(s(1, 1) == 3);
        REQUIRE(s(2, 2) == 4);
        REQUIRE(s(3, 3) == 1);

        auto t = Matrix::TranslationMatrix(2, 3, 4);

        REQUIRE(t(0, 0) == 1);
        REQUIRE(t(1, 1) == 1);
        REQUIRE(t(2, 2) == 1);
        REQUIRE(t(3, 3) == 1);
        REQUIRE(t(0, 3) == 2);
        REQUIRE(t(1, 3) == 3);
        REQUIRE(t(2, 3) == 4);

        auto m = Matrix(4, 4, 0, sf::Color());
        m(0, 0) = 5;
        m(1, 0) = 3;
        m(2, 0) = 2;
        m(3, 0) = 41;
        m(0, 1) = 6;
        m(1, 1) = 5;
        m(2, 1) = 3;
        m(3, 1) = 2;
        m(0, 2) = 8;
        m(1, 2) = 10;
        m(2, 2) = 10;
        m(3, 2) = 2;
        m(0, 3) = 24;
        m(1, 3) = 1;
        m(2, 3) = 3;
        m(3, 3) = 1;

        auto m2 = t * m;
        REQUIRE(m2(0, 0) == 87);
        REQUIRE(m2(1, 0) == 126);
        REQUIRE(m2(2, 0) == 166);
        REQUIRE(m2(3, 0) == 41);
        REQUIRE(m2(0, 1) == 10);
        REQUIRE(m2(1, 1) == 11);
        REQUIRE(m2(2, 1) == 11);
        REQUIRE(m2(3, 1) == 2);
        REQUIRE(m2(0, 2) == 12);
        REQUIRE(m2(1, 2) == 16);
        REQUIRE(m2(2, 2) == 18);
        REQUIRE(m2(3, 2) == 2);
        REQUIRE(m2(0, 3) == 26);
        REQUIRE(m2(1, 3) == 4);
        REQUIRE(m2(2, 3) == 7);
        REQUIRE(m2(3, 3) == 1);
    }
}

TEST_CASE("min & max of matrix", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("cube.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());
    auto truncateAmount = 10000.0;

    REQUIRE((int)(target.minX() * truncateAmount) / truncateAmount == -6.8532);
    REQUIRE((int)(target.maxX() * truncateAmount) / truncateAmount == 6.8532);

    REQUIRE((int)(target.minY() * truncateAmount) / truncateAmount == -0.5077);
    REQUIRE((int)(target.maxY() * truncateAmount) / truncateAmount == 0.5077);

    REQUIRE((int)(target.minZ() * truncateAmount) / truncateAmount == -2.6033);
    REQUIRE((int)(target.maxZ() * truncateAmount) / truncateAmount == 2.6033);
}

TEST_CASE("distance calcualtion", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("target.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());

    REQUIRE(target.getRadius() == 1.0);
}