#ifndef LINAL_ASSESSMENT_MATRIX_H
#define LINAL_ASSESSMENT_MATRIX_H

#include <vector>
#include <SFML/Graphics/Vertex.hpp>
#include "Vector2D.h"
#include <SFML/Graphics.hpp>

typedef unsigned int coordindate;

class Matrix
{
public:
    Matrix(const Matrix &other);
    Matrix(unsigned int rows, unsigned int columns, double value = 0.0);

    static Matrix NullMatrix(unsigned int rows, unsigned int columns);
    static Matrix UnitMatrix(unsigned int size);
    static Matrix TranslationMatrix(double xTranslation, double yTranslation);
    static Matrix ScalingMatrix(double xScalar, double yScalar);
    static Matrix RotationMatrix(int degree);
    static Matrix Matrix2D(unsigned int columns);

    void print() const;

    virtual Matrix operator*(Matrix &scalar);
    virtual Vector2D& operator*(Vector2D &vector);
    virtual Matrix operator*=(Matrix &scalar);
    double& operator()(const unsigned int &row, const unsigned int &column);

    void scale(double xValue, double yValue);
    void translate(double xValue, double yValue);
    void draw(sf::RenderWindow& window) const;
    void rotate(int amountInDegree);

    Vector2D get(unsigned int column) const;
    const Vector2D getOrigin() const;
    unsigned int getRows() const;
    unsigned int getColumns() const;

    std::vector<sf::Vertex> getSFVertices() const;
protected:
    unsigned int rows;
    unsigned int columns;
    std::vector<std::vector<double>> matrix;

    static double toRadial(int degree);
};


#endif //LINAL_ASSESSMENT_MATRIX_H
