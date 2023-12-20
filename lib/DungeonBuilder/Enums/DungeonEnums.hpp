#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class Tile
{
	Unused,
	DirtWall,
	DirtFloor,
	Corridor,
	Door,
	UpStairs,
	DownStairs
};

enum class Direction
{
	North, South, East, West,
};

#endif