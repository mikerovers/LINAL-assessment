#ifndef LINAL_ASSESSMENT_MATRIX_H
#define LINAL_ASSESSMENT_MATRIX_H

#include <vector>
#include <SFML/Graphics/Vertex.hpp>
#include "Vector2D.h"
#include "obj/objload.h"
#include "Vector3D.h"
#include "CustomView.h"
#include <SFML/Graphics.hpp>

typedef unsigned int coordindate;

enum CollisionShape {
    RECTANGLE,
    SPHERE
};

class Matrix
{
public:
    Matrix(const Matrix &other);
    Matrix(unsigned int rows, unsigned int columns, double value = 0.0, sf::Color color = sf::Color::Red,
           CollisionShape collisionShape = CollisionShape::RECTANGLE);

    static Matrix NullMatrix(unsigned int rows, unsigned int columns);
    static Matrix UnitMatrix(unsigned int size);
    static Matrix TranslationMatrix(double xTranslation, double yTranslation, double zTranslation);
    static Matrix ScalingMatrix(double xScalar, double yScalar, double zScalar);
    static Matrix RotationMatrix(int degree);
    static Matrix YRotationMatrix(int degree);
    static Matrix ZRotationMatrix(int degree);
    static Matrix XRotationMatrix(int degree);
    static Matrix Matrix2D(unsigned int columns);
    static Matrix Matrix3D(unsigned int columns);
    static Matrix FromModel(obj::Model model);

    void print() const;

    virtual Matrix operator*(Matrix &scalar);
    virtual Vector3D operator*(Vector3D &vector);
    virtual Matrix operator*=(Matrix &scalar);
    double& operator()(const unsigned int &row, const unsigned int &column);

    void scale(double xValue, double yValue, double zValue);
    void translate(double xValue, double yValue, double zValue);
    void draw(sf::RenderWindow& window, ViewType viewType) const;
    void rotate(int amountInDegree);
    void rotateY(int amountInDegree);
    void rotateZ(int amountInDegree);
    void rotateX(int amountInDegree);
    void rotateAroundPoint(Vector3D &point, double amountInDegree);

    Vector3D get(unsigned int column) const;
    const Vector3D getOrigin() const;
    unsigned int getRows() const;
    unsigned int getColumns() const;

    std::vector<sf::Vertex> getSFVertices() const;
    void setColor(const sf::Color &color);
    double maxX() const;
    double minX() const;
    double minY() const;
    double maxY() const;
    double minZ() const;
    double maxZ() const;
    void addVector(int position, double x, double y, double z);

    CollisionShape getCollisionShape() const
    { return collisionShape; };
    double getRadius() const;
    void setCollisionShape(CollisionShape collisionShape);
    bool intersect(const Matrix &other) const;
    unsigned int rows;
    unsigned int columns;
    std::vector<std::vector<double>> matrix;
    virtual void act() {}
protected:

    sf::Color color;

    static double toRadial(int degree);
    void virtualRotate(Matrix& rotationMatrix);
    CollisionShape collisionShape;
};


#endif //LINAL_ASSESSMENT_MATRIX_H