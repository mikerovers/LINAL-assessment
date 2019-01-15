#ifndef LINAL_ASSESSMENT_BULLET_H
#define LINAL_ASSESSMENT_BULLET_H

#include "Matrix.h"

class Bullet : public Matrix
{
public:
	explicit Bullet(const Matrix &other);
	void act() override;
	const Vector3D &getDirection() const;
	void setDirection(const Vector3D &direction);
	int getLifetime() const;
	void setLifetime(int lifetime);
	void setSpeedVector(Vector3D const newSpeedVector) { speedVector = newSpeedVector; }
	void setSpeedBoost(bool const boost) { hasSpeedBoost = boost; }
private:
	Vector3D direction;
	Vector3D speedVector;
	int lifetime;
	bool hasSpeedBoost = false;
};


#endif //LINAL_ASSESSMENT_BULLET_H
