//
// Created by jamie on 4/6/2021.
//

#include "WiimotePixart.h"

WiimotePixart camera(PB_9, PB_8);

int main()
{
	printf("Booting camera...\n");
	camera.begin();
}

