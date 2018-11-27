#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Matrix.h"
#include "Vector2D.h"
#include <cmath>

Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    columns = other.columns;
    matrix = other.matrix;
}

Matrix::Matrix(unsigned int rows, unsigned int columns, double value): rows(rows), columns(columns)
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

Matrix Matrix::TranslationMatrix(double xTranslation, double yTranslation)
{
    auto m = Matrix{3, 3, 0.0};

    for (unsigned int i = 0; i < 3; ++i) {
        m(i, i) = 1;
    }

    m(0, 2) = xTranslation;
    m(1, 2) = yTranslation;

    return m;
}

Matrix Matrix::ScalingMatrix(double xScalar, double yScalar)
{
    auto m = Matrix{3, 3, 0.0};

    m(0,0) = xScalar;
    m(1, 1) = yScalar;
    m(2, 2) = 1;

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

void Matrix::translate(double xValue, double yValue)
{
    auto t = Matrix::TranslationMatrix(xValue, yValue);

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex  = Vector2D{matrix[0][i], matrix[1][i]};
        t * vertex;

        matrix[0][i] = vertex.getX();
        matrix[1][i] = vertex.getY();
    }
}

Vector2D& Matrix::operator*(Vector2D &vector)
{
    auto m = Matrix{3, 1};
    m(0, 0) = vector.getX();
    m(1, 0) = vector.getY();
    m(2, 0) = 1;

    Matrix& p = *this;
    auto m2 = p * m;

    vector.setX(m2(0, 0));
    vector.setY(m2(1, 0));

    return vector;
}

void Matrix::draw(sf::RenderWindow &window) const
{
    for (auto i = 0 ; i < getColumns(); ++i) {
        for (auto j = i ; j < getColumns(); ++j) {
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(static_cast<float>(matrix[0][i]), static_cast<float>(matrix[1][i])), sf::Color::Red, sf::Vector2f(0.0f, 0.0f)),
                    sf::Vertex(sf::Vector2f(static_cast<float>(matrix[0][j]), static_cast<float>(matrix[1][j])), sf::Color::Red, sf::Vector2f(0.0f, 0.0f))
            };

            window.draw(line, 2, sf::Lines);
        }
    }
}

void Matrix::scale(double xValue, double yValue)
{
    auto origin = getOrigin();
    auto s1 = Matrix::ScalingMatrix(xValue, yValue);
    auto t1 = Matrix::TranslationMatrix(origin.getX(), origin.getY());
    auto t2 = Matrix::TranslationMatrix(-1 * origin.getX(), -1 * origin.getY());

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex = Vector2D{matrix[0][i], matrix[1][i]};
        t2 * vertex;
        s1 * vertex;
        t1 * vertex;

        matrix[0][i] = vertex.getX();
        matrix[1][i] = vertex.getY();
    }
}

void Matrix::rotate(int amountInDegree)
{
    auto origin = getOrigin();
    auto r1 = Matrix::RotationMatrix(amountInDegree);
    auto t1 = Matrix::TranslationMatrix(origin.getX(), origin.getY());
    auto t2 = Matrix::TranslationMatrix(-1 * origin.getX(), -1 * origin.getY());

    for (coordindate i = 0; i < getColumns(); ++i) {
        auto vertex = Vector2D{matrix[0][i], matrix[1][i]};
        t2 * vertex;
        r1 * vertex;
        t1 * vertex;

        matrix[0][i] = vertex.getX();
        matrix[1][i] = vertex.getY();
    }
}

Vector2D Matrix::get(unsigned int column) const
{
    return Vector2D{matrix[0][column], matrix[1][column]};
}

const Vector2D Matrix::getOrigin() const
{
    auto v = Vector2D();

    for (unsigned int i = 0; i < getColumns(); i++) {
        v = v + get(i);
    }

    v.setX(v.getX() / getColumns());
    v.setY(v.getY() / getColumns());

    return v;
}

double Matrix::toRadial(int degree)
{
    return degree * M_PI / 180;
}
