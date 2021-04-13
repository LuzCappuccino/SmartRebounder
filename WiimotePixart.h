//
// Created by jamie on 4/6/2021.
//

#ifndef MBED_CMAKE_TEST_PROJECT_WIIMOTEPIXART_H
#define MBED_CMAKE_TEST_PROJECT_WIIMOTEPIXART_H

#include <mbed.h>

#include <array>

class WiimotePixart
{
private:
	I2C i2c;

	const uint8_t pixartI2CAddr = 0x58;

	const int readDataLength = 16;

	const uint8_t levelParams[5][4] = {
		{ 0x72, 0x20, 0x1F, 0x03},
		{ 0xC8, 0x36, 0x35, 0x3},
		{ 0xAA, 0x64, 0x63, 0x03},
		{ 0x96, 0xB4, 0xB3, 0x04}, 
		{ 0x96, 0xFE, 0xFE, 0x05}
	};

	template<size_t N>
	void writeCommand(std::array<uint8_t, N> bytes)
	{
		if(i2c.write(pixartI2CAddr << 1, reinterpret_cast<char*>(bytes.data()), N) != 0)
		{
			printf("Didn't receive ACK from Pixart sensor");
		}
	}

	void readCommand(char* readData)
	{
		if(i2c.read(((pixartI2CAddr << 1) | 0x01), readData, readDataLength)) {
			printf("Didn't receive ACK from Pixart sensor");
		}
	}

public:
	WiimotePixart(PinName sda, PinName scl):
	i2c(sda, scl)
	{
		i2c.frequency(400000);
	}

	/**
	 * Initializes the sensor
	 */
	void begin();

	/**
	 * Set the sensitivity level of the IR camera, from 1-5.
	 * @param level
	 */
	void setSensitivity(int level);

#define PIXART_MAX_COORDS 4
	/**
	 * Read coordinates of up to 4 detected IR blobs in the camera's field of view.
	 * @return
	 */
	std::array<std::pair<float, float>, PIXART_MAX_COORDS> readCoordinates();

};


#endif //MBED_CMAKE_TEST_PROJECT_WIIMOTEPIXART_H
