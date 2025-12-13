#pragma once
#ifndef DIRECTION_H
#define DIRECTION_H

#include <types/coordinate.h>

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	INVALID
};

inline Coordinate DirectionToCoordinate(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		return Coordinate(0, -1);
	case Direction::DOWN:
		return Coordinate(0, 1);
	case Direction::LEFT:
		return Coordinate(-1, 0);
	case Direction::RIGHT:
		return Coordinate(1, 0);
	default:
		return Coordinate(0, 0);
	}
}

#endif // DIRECTION_H