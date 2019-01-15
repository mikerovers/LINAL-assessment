#include "Player.h"

Player::Player(const Matrix & other) : Matrix(other), shootTimer(125)
{
	rows = other.rows;
	columns = other.columns;
	matrix = other.matrix;
}

void Player::act()
{
	if (speed != 0) {
		auto multiplier = 30 - speed;
		auto currentMatrix = matrix;
		this->translate(heading.getX() / multiplier, heading.getY() / multiplier, heading.getZ() / multiplier);

		Vector3D oldVector, newVector;
		for (coordindate i = 0; i < getColumns(); ++i) {
			oldVector = Vector3D{ matrix[0][i], matrix[1][i], matrix[2][i] };
			newVector = Vector3D{ currentMatrix[0][i], currentMatrix[1][i], currentMatrix[2][i] };
		}

		speedVector = Vector3D{ oldVector.getX() - newVector.getX(), oldVector.getY() - newVector.getY(), oldVector.getZ() - newVector.getZ() };

	}

	if (shootTimer != 0) {
		--shootTimer;
	}
}

int Player::getShootTimer() const
{
	return shootTimer;
}

void Player::setShootTimer(int shootTimer)
{
	Player::shootTimer = shootTimer;
}
