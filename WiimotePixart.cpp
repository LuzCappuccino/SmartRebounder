//
// Created by jamie on 4/6/2021.
//

#include "WiimotePixart.h"

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

}

std::array<std::pair<float, float>, PIXART_MAX_COORDS> WiimotePixart::readCoordinates()
{
	return std::array<std::pair<float, float>, 4>();
}
