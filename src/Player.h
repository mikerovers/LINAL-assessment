#pragma once
#include "src/Matrix.h"
class Player :
	public Matrix
{
public:
	Player(const Matrix &other);
	~Player();
};

