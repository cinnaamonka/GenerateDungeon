#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include "../DungeonMap/DungeonMap.h"

#pragma once
class DungeonGenerator {
public:
	int Seed;
	int XSize, YSize;
	int MaxFeatures;
	int ChanceRoom, ChanceCorridor;

	DungeonGenerator(const int width, const int height, const int MaxFeatures = 100, const int ChanceRoom = 75, const int ChanceCorridor = 25);

	DungeonMap Generate();

private:
	typedef std::mt19937 RngT;

	int GetRandomInt(RngT& rng, const int min, const int max) const;
	Direction GetRandomDirection(RngT& rng) const;
	bool MakeCorridor(DungeonMap& map, RngT& rng, const int x, const int y, const int maxLength, const Direction direction) const;
	bool MakeRoom(DungeonMap& map, RngT& rng, const int x, const int y, const int xMaxLength, const int yMaxLength, const Direction direction) const;
	bool MakeFeature(DungeonMap& map, RngT& rng, const int x, const int y, const int xmod, const int ymod, const Direction direction) const;
	bool MakeFeature(DungeonMap& map, RngT& rng) const;
	bool MakeStairs(DungeonMap& map, RngT& rng, const Tile tile) const;
	bool MakeDungeon(DungeonMap& map, RngT& rng) const;
};

#endif