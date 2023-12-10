#include "TileMapper.h"

TileMapper::TileMapper() {}

std::map<Tile, std::string> TileMapper::tileMap = {
	{Tile::Unused, "lightGray"},
	{Tile::DirtWall,"darkerGray"},
	{Tile::DirtFloor, "gray"},
	{Tile::Corridor, "darkGray"},
	{Tile::Door, "brown"},
	{Tile::UpStairs, "mediumSpringGreen"},
	{Tile::DownStairs,"blueViolet"},
};