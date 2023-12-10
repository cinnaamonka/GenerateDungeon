#include <iostream>
#include <map>
#include <string>
#include <windows.h>

#pragma once
class ColorMapper {
public:
	ColorMapper();

	static COLORREF getColor(const std::string& colorName) { return colorMap[colorName]; }

private:
	static std::map<std::string, COLORREF> colorMap;
};