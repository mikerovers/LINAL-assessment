#include "Bullet.h"
#include "Matrix.h"

Bullet::Bullet(const Matrix &other) : Matrix(other)
{

}

void Bullet::act()
{
	double x, y, z;
	if (hasSpeedBoost) {
		x = direction.getX() + speedVector.getX();
		y = direction.getY() + speedVector.getY();
		z = direction.getZ() + speedVector.getZ();
	}
	else {
		x = direction.getX();
		y = direction.getY();
		z = direction.getZ();
	}

	translate(x, y, z);
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
