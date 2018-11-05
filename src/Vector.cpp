#include "Vector.h"

double Vector::getX() const
{
    return x;
}

double Vector::getY() const
{
    return y;
}


Vector::Vector(double x, double y): x(x), y(y)
{

}

Vector &Vector::operator+(const Vector &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector &Vector::operator-(const Vector &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector &Vector::operator*(const int scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

double Vector::length() const
{
    return sqrt((x * x) + (y * y));
}

void Vector::normalize()
{
    auto length = this->length();
    x = x / length;
    y = y / length;
}

