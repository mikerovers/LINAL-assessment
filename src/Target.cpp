#include "Target.h"

Target::Target(const Matrix & other)
{
	rows = other.rows;
	columns = other.columns;
	matrix = other.matrix;
}

Target::~Target()
{
}