#ifndef UART_H
#define UART_H

#include "driver.h"

class UART{
public:
	UART_HandleTypeDef * huart;

	UART(UART_HandleTypeDef * huart): huart(huart) {}

	void write(uint8_t data){
		HAL_UART_Transmit(huart, (uint8_t *)&data, 1, 100);
	}

	void write(uint8_t *datas, uint32_t len){
		HAL_UART_Transmit(huart, datas, len, 100);
	}

};

#endif
