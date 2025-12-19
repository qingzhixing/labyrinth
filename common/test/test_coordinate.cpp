#include <types/coordinate.h>
#include <testkit.h>

UnitTest(Coordinate_OperatorAdd)
{
	Coordinate a(1, 2);
	Coordinate b(3, 4);
	Coordinate c = a + b;
	assert(c == Coordinate(4, 6));
}

UnitTest(Coordinate_OperatorSubtract)
{
	Coordinate a(1, 2);
	Coordinate b(3, 4);
	Coordinate c = a - b;
	assert(c == Coordinate(-2, -2));
}

UnitTest(Coordinate_IsValid)
{
	assert(Coordinate(1, 2).IsPositive());
	assert(!Coordinate(-1, 2).IsPositive());
	assert(!Coordinate(1, -2).IsPositive());
	assert(!Coordinate(-1, -2).IsPositive());
}
