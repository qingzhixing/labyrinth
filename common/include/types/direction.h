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

Coordinate DirectionToCoordinate(Direction direction);

#endif // DIRECTION_H