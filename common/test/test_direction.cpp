#include <types/direction.h>
#include <types/coordinate.h>
#include <testkit.h>

UnitTest(DirectionToCoordinate)
{
	assert(DirectionToCoordinate(Direction::UP) == Coordinate(-1, 0));
	assert(DirectionToCoordinate(Direction::DOWN) == Coordinate(1, 0));
	assert(DirectionToCoordinate(Direction::LEFT) == Coordinate(0, -1));
	assert(DirectionToCoordinate(Direction::RIGHT) == Coordinate(0, 1));
	assert(DirectionToCoordinate(Direction::INVALID) == Coordinate(0, 0));
}
