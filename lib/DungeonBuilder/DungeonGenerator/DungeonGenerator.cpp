#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator(const int width, const int height, const int MaxFeatures, const int ChanceRoom, const int ChanceCorridor)
	: Seed(std::random_device()()), XSize(width), YSize(height), MaxFeatures(MaxFeatures), ChanceRoom(ChanceRoom), ChanceCorridor(ChanceCorridor) {}

DungeonMap DungeonGenerator::Generate() {
	assert(MaxFeatures > 0);
	assert(XSize > 3);
	assert(YSize > 3);

	std::mt19937 rng = RngT(Seed);
	DungeonMap map = DungeonMap(XSize, YSize, Tile::Unused);

	MakeDungeon(map, rng);

	return map;
}

int DungeonGenerator::GetRandomInt(RngT& rng, const int min, const int max) const {
	return std::uniform_int_distribution<int>(min, max)(rng);
}

Direction DungeonGenerator::GetRandomDirection(RngT& rng) const {
	return Direction(std::uniform_int_distribution<int>(0, 3)(rng));
}

bool DungeonGenerator::MakeCorridor(DungeonMap& map, RngT& rng, const int x, const int y, const int maxLength, const Direction direction) const {
	assert(x >= 0 && x < XSize);
	assert(y >= 0 && y < YSize);
	assert(maxLength > 0 && maxLength <= std::max(XSize, YSize));

	int length = GetRandomInt(rng, 2, maxLength);

	int xStart = x;
	int yStart = y;
	int xEnd = x;
	int yEnd = y;

	switch (direction) {
	case Direction::North:
		yStart = y - length;
		break;
	case Direction::South:
		yEnd = y + length;
		break;
	case Direction::West:
		xStart = x - length;
		break;
	case Direction::East:
		xEnd = x + length;
		break;
	}

	if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd)) { return false; }

	if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd)) { return false; }

	map.SetCells(xStart, yStart, xEnd, yEnd, Tile::Corridor);

	return true;
}

bool DungeonGenerator::MakeRoom(DungeonMap& map, RngT& rng, const int x, const int y, const int xMaxLength, const int yMaxLength, const Direction direction) const {
	int xLength = GetRandomInt(rng, 4, xMaxLength);
	int yLength = GetRandomInt(rng, 4, yMaxLength);

	int xStart = x;
	int yStart = y;
	int xEnd = x;
	int yEnd = y;

	switch (direction) {
	case Direction::North:
		yStart = y - yLength;
		xStart = x - xLength / 2;
		xEnd = x + (xLength + 1) / 2;
		break;
	case Direction::South:
		yEnd = y + yLength;
		xStart = x - xLength / 2;
		xEnd = x + (xLength + 1) / 2;
		break;
	case Direction::West:
		yStart = y - yLength / 2;
		yEnd = y + (yLength + 1) / 2;
		xStart = x - xLength;
		break;
	case Direction::East:
		yStart = y - yLength / 2;
		yEnd = y + (yLength + 1) / 2;
		xEnd = x + xLength;
		break;
	}

	if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd)) { return false; }

	if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd)) { return false; }

	map.SetCells(xStart, yStart, xEnd, yEnd, Tile::DirtWall);
	map.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, Tile::DirtFloor);

	return true;
}

bool DungeonGenerator::MakeFeature(DungeonMap& map, RngT& rng, const int x, const int y, const int xmod, const int ymod, const Direction direction) const {
	const int chance = GetRandomInt(rng, 0, 100);

	const int xMaxLength = 8;
	const int yMaxLength = 6;

	if (chance <= ChanceRoom) {
		if (MakeRoom(map, rng, x + xmod, y + ymod, xMaxLength, yMaxLength, direction)) {
			map.SetCell(x, y, Tile::Door);
			map.SetCell(x + xmod, y + ymod, Tile::DirtFloor);

			return true;
		}

		return false;
	}
	else {
		if (MakeCorridor(map, rng, x + xmod, y + ymod, yMaxLength, direction)) {
			map.SetCell(x, y, Tile::Door);

			return true;
		}

		return false;
	}
}

bool DungeonGenerator::MakeFeature(DungeonMap& map, RngT& rng) const {
	int maxTries = XSize * YSize;

	for (int tries = 0; tries < maxTries; ++tries) {
		int x = GetRandomInt(rng, 1, XSize - 2);
		int y = GetRandomInt(rng, 1, YSize - 2);

		if (map.GetCell(x, y).data.second != Tile::DirtWall && map.GetCell(x, y).data.second != Tile::Corridor) { continue; }

		if (map.IsAdjacent(x, y, Tile::Door)) { continue; }

		if (map.GetCell(x, y + 1).data.second == Tile::DirtFloor || map.GetCell(x, y + 1).data.second == Tile::Corridor) {
			if (MakeFeature(map, rng, x, y, 0, -1, Direction::North)) { return true; }
		}
		else if (map.GetCell(x - 1, y).data.second == Tile::DirtFloor || map.GetCell(x - 1, y).data.second == Tile::Corridor) {
			if (MakeFeature(map, rng, x, y, 1, 0, Direction::East)) { return true; }
		}
		else if (map.GetCell(x, y - 1).data.second == Tile::DirtFloor || map.GetCell(x, y - 1).data.second == Tile::Corridor) {
			if (MakeFeature(map, rng, x, y, 0, 1, Direction::South)) { return true; }
		}
		else if (map.GetCell(x + 1, y).data.second == Tile::DirtFloor || map.GetCell(x + 1, y).data.second == Tile::Corridor) {
			if (MakeFeature(map, rng, x, y, -1, 0, Direction::West)) { return true; }
		}
	}

	return false;
}

bool DungeonGenerator::MakeStairs(DungeonMap& map, RngT& rng, const Tile tile) const {
	int maxTries = XSize * YSize;

	for (int tries = 0; tries < maxTries; ++tries) {
		int x = GetRandomInt(rng, 1, XSize - 2);
		int y = GetRandomInt(rng, 1, YSize - 2);

		if (!map.IsAdjacent(x, y, Tile::DirtFloor) && !map.IsAdjacent(x, y, Tile::Corridor)) { continue; }

		if (map.IsAdjacent(x, y, Tile::Door)) { continue; }

		map.SetCell(x, y, tile);

		return true;
	}

	return false;
}

bool DungeonGenerator::MakeDungeon(DungeonMap& map, RngT& rng) const {
	MakeRoom(map, rng, XSize / 2, YSize / 2, 8, 6, GetRandomDirection(rng));

	for (int features = 1; features < MaxFeatures; ++features) {
		if (!MakeFeature(map, rng)) { break; }
	}

	MakeStairs(map, rng, Tile::UpStairs);
	MakeStairs(map, rng, Tile::DownStairs);

	return true;
}