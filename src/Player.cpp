#include "Player.h"

Player::Player(const Matrix & other): Matrix(other)
{
	rows = other.rows;
	columns = other.columns;
	matrix = other.matrix;
}

Player::Player(unsigned int columns): Matrix(3, columns)
{}

void Player::act()
{
	Matrix::act();
}
