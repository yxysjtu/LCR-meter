#ifndef ADC_H
#define ADC_H

#include "driver.h"

class ADC{
public:
	ADC_HandleTypeDef * hadc;
	bool busy = false;
	void (*sample_complete_handler)() = nullptr;

	ADC(ADC_HandleTypeDef * hadc) : hadc(hadc) {}

	inline void read_dma(uint16_t* buffer, uint32_t len) {
		busy = true;
		HAL_ADC_Start_DMA(hadc, (uint32_t*)buffer, len);
	}

	void interrupt_handler(){
		busy = false;
		if(sample_complete_handler != nullptr) sample_complete_handler();
	}

private:

};

#endif
