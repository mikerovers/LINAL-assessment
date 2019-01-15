#pragma once
#include "Matrix.h"
class Target :
	public Matrix
{
public:
	explicit Target(const Matrix &other);
	~Target();
	void act() override;
};

