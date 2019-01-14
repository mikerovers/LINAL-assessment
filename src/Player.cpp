#include "Player.h"

Player::Player(const Matrix & other)
{
	rows = other.rows;
	columns = other.columns;
	matrix = other.matrix;
}

Player::~Player()
{
}
