#include "types/map_size.h"

MapSize::MapSize() : lines(0), columns(0) {}

MapSize::MapSize(int lines, int columns) : lines(lines), columns(columns) {}

bool MapSize::operator==(const MapSize &other) const
{
	return lines == other.lines && columns == other.columns;
}