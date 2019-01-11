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
    return sqrt((x * x) + (y * y) + (z * z));
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

void Vector3D::draw(sf::RenderWindow &window, const ViewType &viewType) const
{
    sf::CircleShape shape(5.f);

    switch (viewType) {
        case front:
            shape.setPosition(static_cast<float>(getX()), static_cast<float>(getY()));
            break;
        case perspective:break;
        case side:
            shape.setPosition(static_cast<float>(getY()), static_cast<float>(getZ()));
            break;
        case top:
            shape.setPosition(static_cast<float>(getX()), static_cast<float>(getZ()));
            break;
    }

    shape.setFillColor(sf::Color::Blue);
    window.draw(shape);
}

double Vector3D::distance(const Vector3D &other) const
{
    return std::sqrt(std::pow(getX() - other.getX(), 2) + std::pow(getY() - other.getY(), 2) + std::pow(getZ() - other.getZ(), 2));
}

Vector3D Vector3D::crossProduct(const Vector3D &other) const
{
    Vector3D m {};

    m.setX((getY() * other.getZ()) - (getZ() * other.getY()));
    m.setY((getZ() * other.getX()) - (getX() * other.getZ()));
    m.setZ((getX() * other.getY()) - (getY() * other.getX()));

    return m;
}

double Vector3D::inProduct(const Vector3D &other) const
{
    return (getX() * other.getX()) + (getY() * other.getY()) + (getZ() * other.getZ());
}

double Vector3D::angle(const Vector3D &other) const
{
    return (inProduct(other)) / (length() * other.length()) * 180 / M_PI;
}
