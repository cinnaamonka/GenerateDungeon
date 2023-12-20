#ifndef DUNGEON_MAP_H
#define DUNGEON_MAP_H

#include <random>
#include <cassert>

#include "../Enums/DungeonEnums.hpp"
#include "../Structs/DungeonStructs.hpp"

#pragma once
class DungeonMap {
public:
	DungeonMap();
	DungeonMap(const int x, const int y, Tile value = Tile::Unused);

	std::vector<DungeonCell> GetCells() const { return data; };
	DungeonCell GetCell(const int x, const int y) const;

	void SetCell(const int x, const int y, Tile cellType);
	void SetCells(const int xStart, const int yStart, const int xEnd, const int yEnd, const Tile cellType);

	bool IsAdjacent(const int x, const int y, const Tile tile) const;
	bool IsXInBounds(const int x) const;
	bool IsYInBounds(const int y) const;
	bool IsAreaUnused(const int xStart, const int yStart, const int xEnd, const int yEnd) const;

private:
	int xSize, ySize;
	std::vector<DungeonCell> data;

	int orderIndex;
};

#endif