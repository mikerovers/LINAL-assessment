#ifndef LINAL_ASSESSMENT_VECTOR_H
#define LINAL_ASSESSMENT_VECTOR_H

#include <math.h>

class Vector2D
{
public:
    explicit Vector2D(double x = 0, double = 0);
    Vector2D&operator+(const Vector2D &other);
    Vector2D&operator-(const Vector2D &other);
    Vector2D&operator*(int scalar);
    friend bool operator==(const Vector2D& l, const Vector2D& r);
    friend bool operator!=(const Vector2D& l, const Vector2D& r);

    void print() const;
    double length() const;
    void normalize();

    double getX() const;
    double getY() const;
    void setX(double newX);
    void setY(double newY);
private:
    double x;
    double y;
};


#endif //LINAL_ASSESSMENT_VECTOR_H
