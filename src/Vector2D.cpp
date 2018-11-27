#include <tuple>
#include <iostream>
#include "Vector2D.h"

double Vector2D::getX() const
{
    return x;
}

double Vector2D::getY() const
{
    return y;
}


Vector2D::Vector2D(double x, double y): x(x), y(y)
{

}

Vector2D &Vector2D::operator+(const Vector2D &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2D &Vector2D::operator-(const Vector2D &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2D &Vector2D::operator*(const int scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

double Vector2D::length() const
{
    return sqrt((x * x) + (y * y));
}

void Vector2D::normalize()
{
    auto length = this->length();
    x = x / length;
    y = y / length;
}

bool operator==(const Vector2D &l, const Vector2D &r)
{
    return l.getX() == r.getX() && l.getY() == r.getY();
}

bool operator!=(const Vector2D &l, const Vector2D &r)
{
    return !(l == r);
}

void Vector2D::setX(const double newX)
{
    x = newX;
}

void Vector2D::setY(const double newY)
{
    y = newY;
}

void Vector2D::print() const
{
    std::cout << getX() << std::endl << getY() << std::endl;
}


