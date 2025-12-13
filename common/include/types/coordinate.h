#pragma once
#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
	Coordinate();
	Coordinate(const Coordinate &other);
	Coordinate(int line, int column);

public:
	int line, column;

public:
	bool operator==(const Coordinate &other) const;
	bool operator!=(const Coordinate &other) const;
	Coordinate operator+(const Coordinate &other) const;
	Coordinate operator-(const Coordinate &other) const;
	bool IsValid() const;
};

inline const Coordinate INVALID_COORDINATE = Coordinate(-1, -1);

#endif // COORDINATE_H