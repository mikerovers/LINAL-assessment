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
private:
	int shootTimer;
};

