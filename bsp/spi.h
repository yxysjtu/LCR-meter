#ifndef SPI_H
#define SPI_H

#include "driver.h"

class SPI{
public:
	SPI_HandleTypeDef * hspi;

	SPI(SPI_HandleTypeDef * hspi): hspi(hspi) {}

	void write(uint16_t data){
		HAL_SPI_Transmit(hspi, (uint8_t *)&data, 1, 100);
	}

	void write(uint8_t *datas, uint32_t len){
		HAL_SPI_Transmit(hspi, datas, len, 100);
	}

};

#endif
