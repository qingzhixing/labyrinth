#pragma once
#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate
{
	int line, column;
	Coordinate(int line = -1, int column = -1) : line(line), column(column) {}
	bool operator==(const Coordinate &other) const
	{
		return line == other.line && column == other.column;
	}
};

#endif // COORDINATE_H