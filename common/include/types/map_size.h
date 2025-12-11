#pragma once
#ifndef MAP_SIZE_H
#define MAP_SIZE_H

class MapSize
{
public:
	int lines, columns;

public:
	MapSize(int lines = 0, int columns = 0) : lines(lines), columns(columns) {}
	bool operator==(const MapSize &other) const
	{
		return lines == other.lines && columns == other.columns;
	}
};

inline const MapSize MAX_MAP_SIZE = {100, 100};

#endif // MAP_SIZE_H