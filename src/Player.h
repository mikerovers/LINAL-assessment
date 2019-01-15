#pragma once
#include "Matrix.h"

class Player :
	public Matrix
{
public:
	explicit Player(const Matrix &other);
	~Player() = default;
	void act() override;
	int getShootTimer() const;
	void setShootTimer(int shootTimer);
	Vector3D getSpeedVector() const { return speedVector; }

	int getSpeed() const { return speed; }
	void increaseSpeed() {
		if (speed < MAXSPEED) { speed++; }
		else { speed = MAXSPEED; }
	}
	void decreaseSpeed() {
		if (speed > -MAXSPEED) { speed--; }
		else { speed = -MAXSPEED; }
	}

	void setHeading(Vector3D newHeading) { heading = newHeading; }

private:
	int shootTimer = 0;
	Vector3D heading;
	Vector3D speedVector;
	int speed = 0;
	int const MAXSPEED = 15;
};
