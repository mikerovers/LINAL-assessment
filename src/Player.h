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

	double getSpeed() const { return speed; }
	void increaseSpeed() {
		speed += 1;
		if (speed > MAXSPEED) {
			speed = MAXSPEED;
		}
	}
	void decreaseSpeed() {
		if (speed > -MAXSPEED) {
			speed -= 1;
		}
		else {
			speed = -MAXSPEED;
		}
	}

	void setHeading(Vector3D newHeading) { heading = newHeading; }

private:
	int shootTimer = 0;
	Vector3D heading;
	Vector3D speedVector;
	double speed = 0;
	double const MAXSPEED = 15;
};
