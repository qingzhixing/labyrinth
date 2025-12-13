#pragma once
#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
	Coordinate() : line(0), column(0) {}
	Coordinate(const Coordinate &other) : line(other.line), column(other.column) {}
	Coordinate(int line, int column) : line(line), column(column) {}

public:
	int line, column;

public:
	bool operator==(const Coordinate &other) const
	{
		return line == other.line && column == other.column;
	}

	bool operator!=(const Coordinate &other) const
	{
		return !(this->operator==(other));
	}

	Coordinate operator+(const Coordinate &other) const
	{
		return Coordinate(line + other.line, column + other.column);
	}

	Coordinate operator-(const Coordinate &other) const
	{
		return Coordinate(line - other.line, column - other.column);
	}

	bool IsValid() const
	{
		return line >= 0 && column >= 0;
	}
};

inline const Coordinate INVALID_COORDINATE = Coordinate(-1, -1);

#endif // COORDINATE_H