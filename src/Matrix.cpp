#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Matrix.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include <cmath>

Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    columns = other.columns;
    matrix = other.matrix;
}

Matrix::Matrix(unsigned int rows, unsigned int columns, double value, sf::Color color) : rows(rows), columns(columns), color(color)
{
    matrix.resize(rows);
    for (auto i = 0; i < matrix.size(); ++i) {
        matrix[i].resize(columns, value);
    }
}

unsigned int Matrix::getRows() const
{
    return rows;
}

unsigned int Matrix::getColumns() const
{
    return columns;
}

double &Matrix::operator()(const unsigned int &row, const unsigned int &column)
{
    return matrix[row][column];
}

Matrix Matrix::operator*(Matrix &scalar)
{
    auto tmp = Matrix{scalar.getRows(), scalar.getColumns(), 0.0};
    if (getColumns() == scalar.getRows()) {

        for (auto i = 0; i < getRows(); ++i) {
            for (auto j = 0; j < scalar.getColumns(); ++j) {
                double temp = 0.0;
                for(auto k = 0; k < getColumns(); ++k) {
                    temp += matrix[i][k] * scalar(k, j);
                }

                tmp(i, j) = temp;
            }
        }
    }

    return tmp;
}

void Matrix::print() const
{
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

Matrix Matrix::NullMatrix(unsigned int rows, unsigned int columns)
{
    return Matrix{rows, columns, 0.0};
}

Matrix Matrix::UnitMatrix(unsigned int size)
{
    auto m = Matrix{size, size, 0.0};

    for (unsigned int i = 0; i < size; ++i) {
        m(i, i) = 1;
    }

    return m;
}

Matrix Matrix::TranslationMatrix(double xTranslation, double yTranslation, double zTranslation)
{
    auto m = Matrix{4, 4, 0.0};

    for (unsigned int i = 0; i < 4; ++i) {
        m(i, i) = 1;
    }

    m(0, 3) = xTranslation;
    m(1, 3) = yTranslation;
    m(2, 3) = zTranslation;

    return m;
}

Matrix Matrix::ScalingMatrix(double xScalar, double yScalar, double zScalar)
{
    auto m = Matrix{4, 4, 0.0};

    m(0,0) = xScalar;
    m(1, 1) = yScalar;
    m(2, 2) = zScalar;
    m(3, 3) = 1;

    return m;
}

Matrix Matrix::RotationMatrix(int degree)
{
    auto m = Matrix{4, 4, 0.0};

    auto radial = toRadial(degree);

    m(0, 0) = 1;
    m(1, 1) = cos(radial);
    m(1, 2) = -1 * sin(radial);
    m(2, 1) = sin(radial);
    m(2, 2) = cos(radial);
    m(3, 3) = 1;

    return m;
}

Matrix Matrix::YRotationMatrix(int degree)
{
    auto m = Matrix{4, 4, 0.0};

    auto radial = toRadial(degree);

    m(1, 1) = 1;
    m(3, 3) = 1;
    m(0, 0) = cos(radial);
    m(0, 2) = sin(radial);
    m(2, 0) = -1 * sin(radial);
    m(2, 2) = cos(radial);

    return m;
}

Matrix Matrix::Matrix2D(unsigned int columns)
{
    auto m = Matrix{2, columns, 0.0};

    return m;
}

Matrix Matrix::Matrix3D(unsigned int columns)
{
    auto m = Matrix{3, columns, 0.0};

    return m;
}

Matrix Matrix::FromModel(obj::Model model)
{
    auto m = Matrix{3, static_cast<unsigned int>(model.vertex.size() / 3), 0.0};

    int column = 0;
    int row = 0;
    for (auto c = 0; c < model.vertex.size(); ++c) {
        m(row, column) = model.vertex[c];
        row++;

        if ((c % 3) == 2) {
            ++column;
            row = 0;
        }
    }

    return m;
}

std::vector<sf::Vertex> Matrix::getSFVertices() const
{
    std::vector<sf::Vertex> lines;

    for (auto i = 0 ; i < columns; ++i) {
        auto v = sf::Vertex(sf::Vector2f(static_cast<float>(matrix[0][i]), static_cast<float>(matrix[1][i])), sf::Color::Red, sf::Vector2f(0.0f, 0.0f));
        lines.emplace_back(v);
    }

    return lines;
}

Matrix Matrix::operator*=(Matrix &scalar)
{
    auto result = (*this) * scalar;
    (*this) = result;

    return *this;
}

void Matrix::translate(double xValue, double yValue, double zValue)
{
    auto t = Matrix::TranslationMatrix(xValue, yValue, zValue);

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex  = Vector3D{matrix[0][i], matrix[1][i], matrix[2][i]};
        auto newVector = t * vertex;

        matrix[0][i] = newVector.getX();
        matrix[1][i] = newVector.getY();
        matrix[2][i] = newVector.getZ();
    }
}

Vector3D Matrix::operator*(Vector3D &vector)
{
    auto v = Vector3D(0, 0, 0);
    auto m = Matrix{4, 1};
    m(0, 0) = vector.getX();
    m(1, 0) = vector.getY();
    m(2, 0) = vector.getZ();
    m(3, 0) = 1;

    Matrix& p = *this;
    auto m2 = p * m;

    v.setX(m2(0, 0));
    v.setY(m2(1, 0));
    v.setZ(m2(2, 0));

    return v;
}

void Matrix::draw(sf::RenderWindow &window, const ViewType viewType) const
{
    for (auto i = 0 ; i < getColumns(); ++i) {
        for (auto j = i ; j < getColumns(); ++j) {
            sf::Vertex line[2];
            switch (viewType) {
                case front:
                    line[0] =
                            sf::Vertex(sf::Vector2f(static_cast<float>(matrix[0][i]), static_cast<float>(matrix[1][i])), color, sf::Vector2f(0.0f, 0.0f));
                    line[1] =
                            sf::Vertex(sf::Vector2f(static_cast<float>(matrix[0][j]), static_cast<float>(matrix[1][j])), color, sf::Vector2f(0.0f, 0.0f));

                    break;
                case perspective:break;
                case side:
                    line[0] =
                            sf::Vertex(sf::Vector2f(static_cast<float>(matrix[2][i]), static_cast<float>(matrix[1][i])), color, sf::Vector2f(0.0f, 0.0f));
                    line[1] =
                            sf::Vertex(sf::Vector2f(static_cast<float>(matrix[2][j]), static_cast<float>(matrix[1][j])), color, sf::Vector2f(0.0f, 0.0f));

                    break;
                case top:
                    line[0] =
                            sf::Vertex(sf::Vector2f(static_cast<float>(matrix[0][i]), static_cast<float>(matrix[2][i])), color, sf::Vector2f(0.0f, 0.0f));
                    line[1] =
                            sf::Vertex(sf::Vector2f(static_cast<float>(matrix[0][j]), static_cast<float>(matrix[2][j])), color, sf::Vector2f(0.0f, 0.0f));

                    break;
            }

            window.draw(line, 2, sf::Lines);
        }
    }
}

void Matrix::scale(double xValue, double yValue, double zValue)
{
    auto origin = getOrigin();
    auto s1 = Matrix::ScalingMatrix(xValue, yValue, zValue);
    auto t1 = Matrix::TranslationMatrix(origin.getX(), origin.getY(), origin.getZ());
    auto t2 = Matrix::TranslationMatrix(-1 * origin.getX(), -1 * origin.getY(), -1 * origin.getZ());

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex = Vector3D{matrix[0][i], matrix[1][i], matrix[2][i]};
        auto v1 = t2 * vertex;
        auto v2 = s1 * v1;
        auto v3 = t1 * v2;


        matrix[0][i] = v3.getX();
        matrix[1][i] = v3.getY();
        matrix[2][i] = v3.getZ();
    }
}

void Matrix::rotate(int amountInDegree)
{
    auto r1 = Matrix::RotationMatrix(amountInDegree);
    virtualRotate(r1);
}

void Matrix::virtualRotate(Matrix &rotationMatrix)
{
    auto origin = getOrigin();
    auto t1 = Matrix::TranslationMatrix(origin.getX(), origin.getY(), origin.getZ());
    auto t2 = Matrix::TranslationMatrix(-1 * origin.getX(), -1 * origin.getY(), -1 * origin.getZ());

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex = Vector3D{matrix[0][i], matrix[1][i], matrix[2][i]};
        auto v1 = t2 * vertex;
        auto v2 = rotationMatrix * v1;
        auto v3 = t1 * v2;

        matrix[0][i] = v3.getX();
        matrix[1][i] = v3.getY();
        matrix[2][i] = v3.getZ();
    }
}

void Matrix::rotateY(int amountInDegree)
{
    auto r1 = Matrix::YRotationMatrix(amountInDegree);
    virtualRotate(r1);
}

Vector3D Matrix::get(unsigned int column) const
{
    return Vector3D{matrix[0][column], matrix[1][column], matrix[2][column]};
}

const Vector3D Matrix::getOrigin() const
{
    auto v = Vector3D();

    for (unsigned int i = 0; i < getColumns(); i++) {
        v = v + get(i);
    }

    v.setX(v.getX() / getColumns());
    v.setY(v.getY() / getColumns());
    v.setZ(v.getZ() / getColumns());

    return v;
}

double Matrix::toRadial(int degree)
{
    return degree * M_PI / 180;
}

void Matrix::rotateZ(int amountInDegree)
{
    auto r1 = Matrix::ZRotationMatrix(amountInDegree);
    virtualRotate(r1);
}

Matrix Matrix::ZRotationMatrix(int degree)
{
    auto m = Matrix{4, 4, 0.0};

    auto radial = toRadial(degree);

    m(2, 2) = 1;
    m(3, 3) = 1;
    m(1, 1) = cos(radial);
    m(0, 1) = sin(radial);
    m(1, 0) = -1 * sin(radial);
    m(0, 0) = cos(radial);

    return m;
}

Matrix Matrix::XRotationMatrix(int degree)
{
    auto m = Matrix{4, 4, 0.0};

    auto radial = toRadial(degree);

    m(0, 0) = 1;
    m(3, 3) = 1;
    m(1, 1) = cos(radial);
    m(2, 1) = sin(radial);
    m(1, 2) = -1 * sin(radial);
    m(2, 2) = cos(radial);

    return m;
}

void Matrix::rotateX(int amountInDegree)
{
    auto r1 = Matrix::XRotationMatrix(amountInDegree);
    virtualRotate(r1);
}

void Matrix::rotateAroundPoint(Vector3D &point, double amountInDegree)
{
    auto pointMatrix = Matrix{ 3, 1 };
    pointMatrix(0, 0) = point.getX();
    pointMatrix(1, 0) = point.getY();
    pointMatrix(2, 0) = point.getZ();
    double toXYInDegree = atan((point.getZ() / point.getX())) * 180.0 / M_PI;

    auto r1 = Matrix::YRotationMatrix(static_cast<int>(toXYInDegree));
    std::cout << "Rotation 1:" << std::endl;
    r1.print();
    std::cout << std::endl;

    // Rotate to y axis.
    auto v1 = Matrix::YRotationMatrix(static_cast<int>(toXYInDegree)) * point;
    v1.setZ(0);

    // Rotate to x axis.
    auto slanted = v1.getY() / sqrt(pow(v1.getX(), 2) + pow(v1.getZ(), 2) + pow(v1.getY(), 2));
    auto adjacent = (sqrt(pow(v1.getX(), 2) + pow(v1.getZ(), 2))) / sqrt(pow(v1.getX(), 2) + pow(v1.getZ(), 2) + pow(v1.getY(), 2));
    double toXInDegree = acos(adjacent) * 180.0 / M_PI;
    auto v2 = Matrix::XRotationMatrix(static_cast<int>(toXInDegree)) * v1;

    auto r2 = Matrix::ZRotationMatrix(static_cast<int>(toXInDegree));
    std::cout << "Rotation 2:" << std::endl;
    r2.print();
    std::cout << std::endl;

    auto r3 = Matrix::XRotationMatrix(amountInDegree);
    std::cout << "Rotation 3:" << std::endl;
    r3.print();
    std::cout << std::endl;

    auto r4 = Matrix::ZRotationMatrix(static_cast<int>(-toXInDegree));
    std::cout << "Rotation 4:" << std::endl;
    r4.print();
    std::cout << std::endl;

    auto r5 = Matrix::YRotationMatrix(static_cast<int>(-toXYInDegree));
    std::cout << "Rotation 5:" << std::endl;
    r5.print();
    std::cout << std::endl;

    auto m1 = r5 * r4;
    auto m2 = m1 * r3;
    auto m3 = m2 * r2;
    auto m4 = m3 * r1;

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex = Vector3D{matrix[0][i], matrix[1][i], matrix[2][i]};
        auto nv = m4 * vertex;

        matrix[0][i] = nv.getX();
        matrix[2][i] = nv.getZ();
        matrix[1][i] = nv.getY();
    }
}

void Matrix::setColor(const sf::Color &color)
{
    Matrix::color = color;
}

