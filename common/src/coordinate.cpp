#include <types/coordinate.h>

Coordinate::Coordinate() : row(0), column(0) {}

Coordinate::Coordinate(const Coordinate &other) : row(other.row), column(other.column) {}

Coordinate::Coordinate(int row, int column) : row(row), column(column) {}

bool Coordinate::operator==(const Coordinate &other) const
{
	return row == other.row && column == other.column;
}

bool Coordinate::operator!=(const Coordinate &other) const
{
	return !(this->operator==(other));
}

Coordinate Coordinate::operator+(const Coordinate &other) const
{
	return Coordinate(row + other.row, column + other.column);
}

Coordinate Coordinate::operator-(const Coordinate &other) const
{
	return Coordinate(row - other.row, column - other.column);
}

bool Coordinate::IsPositive() const
{
	return row >= 0 && column >= 0;
}