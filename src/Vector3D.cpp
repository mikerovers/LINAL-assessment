#include <cmath>
#include <iostream>
#include "Vector3D.h"

Vector3D Vector3D::normalize()
{
    Vector3D m{};

    auto length = this->length();
    m.setX(x / length);
    m.setY(y / length);
    m.setZ(z / length);

    return m;
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
            shape.setPosition(static_cast<float>(getZ()), static_cast<float>(getY()));
            break;
        case top:
            shape.setPosition(static_cast<float>(getX()), static_cast<float>(getZ()));
            break;
    }

    shape.setFillColor(sf::Color::Blue);
    window.draw(shape);
}


void Vector3D::draw(sf::RenderWindow &window, const ViewType &viewType, const Vector3D &other) const
{
    sf::Vertex line[2];
    switch (viewType) {
        case front:
            line[0] = sf::Vertex(sf::Vector2f(static_cast<float>(getX()), static_cast<float>(getY())));
            line[1] = sf::Vertex(sf::Vector2f(static_cast<float>(other.getX()), static_cast<float>(other.getY())));
            break;
        case perspective:break;
        case side:
            line[0] = sf::Vertex(sf::Vector2f(static_cast<float>(getZ()), static_cast<float>(getY())));
            line[1] = sf::Vertex(sf::Vector2f(static_cast<float>(other.getZ()), static_cast<float>(other.getY())));
            break;
        case top:
            line[0] = sf::Vertex(sf::Vector2f(static_cast<float>(getX()), static_cast<float>(getZ())));
            line[1] = sf::Vertex(sf::Vector2f(static_cast<float>(other.getX()), static_cast<float>(other.getZ())));
            break;
    }

    window.draw(line, 2, sf::Lines);
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

Vector3D Vector3D::operator+=(const Vector3D &other) const
{
    Vector3D m{};

    m.setX(x + other.getX());
    m.setY(y + other.getY());
    m.setZ(z + other.getZ());

    return m;
}

Vector3D Vector3D::operator*=(int scalar) const
{
    Vector3D m{};

    m.setX(x * scalar);
    m.setY(y *scalar);
    m.setZ(z *scalar);

    return m;
}

Vector3D &Vector3D::mirror(const Vector3D &other)
{
    x = 2 * other.getX() - getX();
    y = 2 * other.getY() - getY();
    z = 2 * other.getZ() - getZ();

    return *this;
}
