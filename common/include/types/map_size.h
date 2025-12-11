#pragma once
#ifndef MAP_SIZE_H
#define MAP_SIZE_H

struct MapSize
{
	int lines, columns;
	MapSize(int lines = 0, int columns = 0) : lines(lines), columns(columns) {}
	bool operator==(const MapSize &other) const
	{
		return lines == other.lines && columns == other.columns;
	}
};

#endif // MAP_SIZE_H