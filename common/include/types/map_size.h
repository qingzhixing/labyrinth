#pragma once
#ifndef MAP_SIZE_H
#define MAP_SIZE_H

class MapSize
{
public:
	int lines, columns;

public:
	MapSize();
	MapSize(int lines, int columns);
	bool operator==(const MapSize &other) const;
};

inline const MapSize MAX_MAP_SIZE(100, 100);

#endif // MAP_SIZE_H