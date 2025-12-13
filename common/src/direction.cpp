#include <types/direction.h>
#include <types/coordinate.h>

Coordinate DirectionToCoordinate(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		return Coordinate(-1, 0);
	case Direction::DOWN:
		return Coordinate(1, 0);
	case Direction::LEFT:
		return Coordinate(0, -1);
	case Direction::RIGHT:
		return Coordinate(0, 1);
	default:
		return Coordinate(0, 0);
	}
}