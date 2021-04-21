//
// Created by jamie on 4/6/2021.
//

#include "WiimotePixart.h"
#include <cinttypes>

void WiimotePixart::begin()
{
	// Commands from here: https://gist.github.com/multiplemonomials/e0ad97062a53ec2d994bd745134cc2f1
	writeCommand<2>({0x30, 0x1});
	writeCommand<2>({0x30, 0x8});
	writeCommand<2>({0x06, 0x90});
	writeCommand<2>({0x08, 0xC0});
	writeCommand<2>({0x1A, 0x40});
	writeCommand<2>({0x33, 0x33});
}

void WiimotePixart::setSensitivity(int level)
{
	writeCommand<2>({0x30, 0x1});
	writeCommand<8>({0x00, 0x02, 0x00, 0x00, 0x71, 0x01, 0x00, levelParams[level - 1][0]});
	writeCommand<3>({0x07, 0x00, levelParams[level - 1][1]});
	writeCommand<3>({0x1A, levelParams[level - 1][2], levelParams[level - 1][3]});
	writeCommand<2>({0x33, 0x03});
	writeCommand<2>({0x30, 0x8});
}

std::pair<float, float> unpackCoords(char* rawCoord) {
	float x = ((rawCoord[2] & 0x30) << 4) + rawCoord[0];
	float y = ((rawCoord[2] & 0xC0) << 2) + rawCoord[1];
	std::pair<float, float> coord(x, y);
	return coord;
}

std::array<std::pair<float, float>, PIXART_MAX_COORDS> WiimotePixart::readCoordinates()
{
	std::array<std::pair<float, float>, 4> coords;
	writeCommand<1>({0x36});
	char rawData[readDataLength];
	readCommand(rawData);

	char coord_0[3] = {rawData[1], rawData[2], rawData[3]};
	char coord_1[3] = {rawData[4], rawData[5], rawData[6]};
	char coord_2[3] = {rawData[7], rawData[8], rawData[9]};
	char coord_3[3] = {rawData[10], rawData[11], rawData[12]};

	coords[0] = unpackCoords(coord_0);
	coords[1] = unpackCoords(coord_1);
	coords[2] = unpackCoords(coord_2);
	coords[3] = unpackCoords(coord_3);

	return coords;
}
