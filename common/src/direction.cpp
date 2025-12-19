#include <types/direction.h>
#include <types/coordinate.h>
#include <string>

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
std::string DirectionToString(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		return std::string("up");
	case Direction::DOWN:
		return std::string("down");
	case Direction::LEFT:
		return std::string("left");
	case Direction::RIGHT:
		return std::string("right");
	default:
		return std::string("invalid");
	}
}