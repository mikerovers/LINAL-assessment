#include "Player.h"

Player::Player(const Matrix & other): Matrix(other), shootTimer(125)
{
	rows = other.rows;
	columns = other.columns;
	matrix = other.matrix;
}

void Player::act()
{
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
