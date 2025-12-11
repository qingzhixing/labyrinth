#pragma once
#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
	int line, column;

public:
	Coordinate(int line = 0, int column = 0) : line(line), column(column) {}
	bool operator==(const Coordinate &other) const
	{
		return line == other.line && column == other.column;
	}

	bool operator!=(const Coordinate &other) const
	{
		return !(this->operator==(other));
	}

	bool IsValid() const
	{
		return line >= 0 && column >= 0;
	}
};

inline const Coordinate INVALID_COORDINATE = Coordinate(-1, -1);

#endif // COORDINATE_H