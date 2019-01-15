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

        REQUIRE(m.getColumns() == 4);
        REQUIRE(m.getRows() == 4);

        REQUIRE(m.get(0).getX() == 5);
        REQUIRE(m.get(0).getY() == 3);
        REQUIRE(m.get(0).getZ() == 2);

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

    REQUIRE((int)(target.minX() * truncateAmount) / truncateAmount == -1);
    REQUIRE((int)(target.maxX() * truncateAmount) / truncateAmount == 1);

    REQUIRE((int)(target.minY() * truncateAmount) / truncateAmount == -1);
    REQUIRE((int)(target.maxY() * truncateAmount) / truncateAmount == 1);

    REQUIRE((int)(target.minZ() * truncateAmount) / truncateAmount == -1);
    REQUIRE((int)(target.maxZ() * truncateAmount) / truncateAmount == 1);
}

TEST_CASE("distance calculation", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("target.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());

    REQUIRE(target.getRadius() == 1.0);
}

TEST_CASE("translation", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("cube.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());

    target.translate(3, 5, 6);

    REQUIRE(target.get(0).getX() == 2);
    REQUIRE(target.get(0).getY() == 4);
    REQUIRE(target.get(0).getZ() == 7);
}

TEST_CASE("rotation", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("cube.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());
    auto truncateAmount = 10000.0;

    target.rotateX(10);

    REQUIRE(target.get(0).getX() == -1);
    REQUIRE((int)(target.get(0).getY() * truncateAmount) / truncateAmount == -1.1584);
    REQUIRE((int)(target.get(0).getZ() * truncateAmount) / truncateAmount == 0.8111);
}

TEST_CASE("scale", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("cube.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());

    target.scale(2, 3, 4);

    REQUIRE(target.get(0).getX() == -2);
    REQUIRE(target.get(0).getY() == -3);
    REQUIRE(target.get(0).getZ() == 4);
}

TEST_CASE("origin", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("cube.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());

    target.translate(3, 5, 6);
    auto origin = target.getOrigin();

    REQUIRE(origin.getX() == 3);
    REQUIRE(origin.getY() == 5);
    REQUIRE(origin.getZ() == 6);
}

TEST_CASE("matrix * matrix", "[matrix]") {
    Matrix m1{2, 2};
    m1(0, 0) = 1;
    m1(1, 0) = 3;
    m1(0, 1) = 2;
    m1(1, 1) = 4;

    Matrix m2{2, 2};
    m2(0, 0) = 5;
    m2(1, 0) = 6;
    m2(0, 1) = 7;
    m2(1, 1) = 8;

    Matrix m3 = m1 * m2;
    REQUIRE(m3(0, 0) == 17);
    REQUIRE(m3(1, 0) == 39);
    REQUIRE(m3(0, 1) == 23);
    REQUIRE(m3(1, 1) == 53);

    Matrix m4{2, 2};
    m4(0, 0) = 1;
    m4(1, 0) = 3;
    m4(0, 1) = 2;
    m4(1, 1) = 4;

    Matrix m5{2, 1};
    m5(0, 0) = 5;
    m5(1, 0) = 6;

    Matrix m6 = m4 * m5;
    REQUIRE(m6(0, 0) == 17);
    REQUIRE(m6(1, 0) == 39);
}

TEST_CASE("intersect", "[matrix]") {
    auto targetMesh = std::make_unique<MyMesh>("cube.obj");
    auto target1 = GameObject::FromModel(targetMesh->getModel());
    auto target2 = GameObject::FromModel(targetMesh->getModel());
    auto target3 = GameObject::FromModel(targetMesh->getModel());
    auto target4 = GameObject::FromModel(targetMesh->getModel());

    target3.translate(3, 3, 3);
    target2.translate(1, 1, 1);

    REQUIRE(target1.intersect(target2));
    REQUIRE(target2.intersect(target3));
    REQUIRE(target3.intersect(target4) == false);
}