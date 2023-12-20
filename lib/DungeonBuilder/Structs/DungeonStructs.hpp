#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <utility>

#include "../Enums/DungeonEnums.hpp"

struct DungeonCell
{
	std::pair<int, Tile> data;

	int orderIndex;
};

#endif