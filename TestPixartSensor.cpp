//
// Created by jamie on 4/6/2021.
//

#include "WiimotePixart.h"

WiimotePixart camera(PB_9, PB_8);

int main()
{
	printf("Booting camera...\n");
	camera.begin();
	printf("Setting sensitivity level...\n");
	camera.setSensitivity(1);
	// camera.setSensitivity(2);
	// camera.setSensitivity(3);
	// camera.setSensitivity(4);
	// camera.setSensitivity(5);

	std::array<std::pair<float, float>, PIXART_MAX_COORDS> coords = camera.readCoordinates();
	printf("Coordinates received...\n");
	for(int i = 0; i < PIXART_MAX_COORDS; i++) {
		printf("%i: (%f, %f) \n", i, coords[i].first, coords[i].second);
	}
}

