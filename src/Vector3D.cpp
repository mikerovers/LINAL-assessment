#include <cmath>
#include <iostream>
#include "Vector3D.h"

void Vector3D::normalize()
{
    auto length = this->length();
    x = x / length;
    y = y / length;
    z = z / length;
}

double Vector3D::length() const
{
    return sqrt((x * x) + (y * y) * (z * z));
}

void Vector3D::print() const
{
    std::cout << getX() << std::endl << getY() << std::endl << getZ() << std::endl;
}

Vector3D &Vector3D::operator*(int scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

Vector3D &Vector3D::operator-(const Vector3D &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3D &Vector3D::operator+(const Vector3D &other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z)
{

}
