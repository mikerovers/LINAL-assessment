#pragma once
#include "Matrix.h"

class Player :
	public Matrix
{
public:
	explicit Player(const Matrix &other);
	~Player();
};

