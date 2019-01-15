#pragma once
#include "Matrix.h"

class Player :
	public Matrix
{
public:
	explicit Player(const Matrix &other);
	explicit Player(unsigned int columns);
	~Player() = default;
	void act() override;
};

