#pragma once
#ifndef DIRECTION_H
#define DIRECTION_H

#include <types/coordinate.h>
#include <string>

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	INVALID
};

Coordinate DirectionToCoordinate(Direction direction);

std::string DirectionToString(Direction direction);

#endif // DIRECTION_H