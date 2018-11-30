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
    auto m = Matrix{3, 3, 0.0};

    auto radial = toRadial(degree);

    m(0, 0) = cos(radial);
    m(0, 1) = -1 * sin(radial);
    m(1, 0) = sin(radial);
    m(1, 1) = cos(radial);
    m(2, 2) = 1;

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

    m.print();

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
    auto origin = getOrigin();
    auto r1 = Matrix::RotationMatrix(amountInDegree);
    auto t1 = Matrix::TranslationMatrix(origin.getX(), origin.getY(), origin.getZ());
    auto t2 = Matrix::TranslationMatrix(-1 * origin.getX(), -1 * origin.getY(), 0);

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex = Vector3D{matrix[0][i], matrix[1][i], matrix[2][i]};
        t2 * vertex;
        r1 * vertex;
        t1 * vertex;

        matrix[0][i] = vertex.getX();
        matrix[1][i] = vertex.getY();
    }
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
