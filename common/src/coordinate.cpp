#include <types/coordinate.h>

Coordinate::Coordinate() : line(0), column(0) {}

Coordinate::Coordinate(const Coordinate &other) : line(other.line), column(other.column) {}

Coordinate::Coordinate(int line, int column) : line(line), column(column) {}

bool Coordinate::operator==(const Coordinate &other) const
{
	return line == other.line && column == other.column;
}

bool Coordinate::operator!=(const Coordinate &other) const
{
	return !(this->operator==(other));
}

Coordinate Coordinate::operator+(const Coordinate &other) const
{
	return Coordinate(line + other.line, column + other.column);
}

Coordinate Coordinate::operator-(const Coordinate &other) const
{
	return Coordinate(line - other.line, column - other.column);
}

bool Coordinate::IsValid() const
{
	return line >= 0 && column >= 0;
}