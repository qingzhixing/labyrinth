#include <types/map_size.h>
#include <testkit.h>

UnitTest(MapSize)
{
	assert(MapSize(0, 0) == MapSize());
	assert(MapSize(1, 2) == MapSize(1, 2));
}