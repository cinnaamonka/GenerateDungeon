#include <iostream>
#include <map>
#include <string>
#include <windows.h>

#include "../../../lib/DungeonBuilder/Enums/DungeonEnums.hpp"

#pragma once
class TileMapper {
public:
	TileMapper();

	static std::string GetColorName(const Tile& colorName) { return tileMap[colorName]; }

private:
	static std::map<Tile, std::string> tileMap;
};