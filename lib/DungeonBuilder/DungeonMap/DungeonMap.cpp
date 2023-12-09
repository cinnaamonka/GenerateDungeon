#include "DungeonMap.h"

DungeonMap::DungeonMap() : xSize(0), ySize(0), data() {}

DungeonMap::DungeonMap(const int x, const int y, const Tile value) : xSize(x), ySize(y), data(x* y, value) {}


Tile DungeonMap::GetCell(const int x, const int y) const {
	assert(IsXInBounds(x) && IsYInBounds(y));
	return data[x + xSize * y];
}

void DungeonMap::SetCell(const int x, const int y, Tile cellType) {
	assert(IsXInBounds(x) && IsYInBounds(y));
	data[x + xSize * y] = cellType;
}

void DungeonMap::SetCells(const int xStart, const int yStart, const int xEnd, const int yEnd, const Tile cellType) {
	assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
	assert(IsYInBounds(yStart) && IsYInBounds(yEnd));
	assert(xStart <= xEnd);
	assert(yStart <= yEnd);

	for (int y = yStart; y <= yEnd; ++y) {
		for (int x = xStart; x <= xEnd; ++x) {
			SetCell(x, y, cellType);
		}
	}
}

bool DungeonMap::IsXInBounds(const int x) const {
	return x >= 0 && x < xSize;
}

bool DungeonMap::IsYInBounds(const int y) const {
	return y >= 0 && y < ySize;
}

bool DungeonMap::IsAreaUnused(const int xStart, const int yStart, const int xEnd, const int yEnd) const {
	assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
	assert(IsYInBounds(yStart) && IsYInBounds(yEnd));
	assert(xStart <= xEnd);
	assert(yStart <= yEnd);

	for (int y = yStart; y <= yEnd; ++y) {
		for (int x = xStart; x <= xEnd; ++x) {
			if (GetCell(x, y) != Tile::Unused) {
				return false;
			}
		}
	}

	return true;
}

bool DungeonMap::IsAdjacent(const int x, const int y, const Tile tile) const {
	assert(IsXInBounds(x - 1) && IsXInBounds(x + 1));
	assert(IsYInBounds(y - 1) && IsYInBounds(y + 1));

	const bool isLeft = GetCell(x - 1, y) == tile;
	const bool isRight = GetCell(x + 1, y) == tile;
	const bool isBottom = GetCell(x, y - 1) == tile;
	const bool isTop = GetCell(x, y + 1) == tile;

	return isLeft || isRight || isBottom || isTop;
}