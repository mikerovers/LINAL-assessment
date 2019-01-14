#pragma once
#include "src/Matrix.h"
class Target :
	public Matrix
{
public:
	Target(const Matrix &other);
	~Target();
};

