#include "ColorMapper.h"


ColorMapper::ColorMapper() {}

std::map<std::string, COLORREF> ColorMapper::colorMap = {
	{"lightGray", RGB(211, 211, 211)},
	{"gray", RGB(128, 128, 128)},
	{"darkGray", RGB(85, 85, 85)},
	{"darkerGray", RGB(40, 40, 40)},
	{"brown", RGB(139, 69, 19)},
	{"mediumAquamarine", RGB(102, 205, 170)},
	{"mediumSlateBlue", RGB(123, 104, 238)},
	{"mediumSpringGreen", RGB(112, 219, 147)},
	{"blueViolet", RGB(138, 43, 226)},
};
