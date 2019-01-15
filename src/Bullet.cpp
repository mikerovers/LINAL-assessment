#include "Bullet.h"
#include "Matrix.h"

Bullet::Bullet(const Matrix &other) : Matrix(other)
{

}

void Bullet::act()
{
    translate(direction.getX(), direction.getY(), direction.getZ());
    setLifetime(getLifetime() - 1);
}

const Vector3D &Bullet::getDirection() const
{
    return direction;
}

void Bullet::setDirection(const Vector3D &direction)
{
    Bullet::direction = direction;
}

int Bullet::getLifetime() const
{
    return lifetime;
}

void Bullet::setLifetime(int lifetime)
{
    Bullet::lifetime = lifetime;
}
