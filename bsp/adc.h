#ifndef ADC_H
#define ADC_H

#include "driver.h"

class ADC{
public:
	ADC_HandleTypeDef * hadc;
	TIM_HandleTypeDef * htim;
	bool busy = false;
	void (*sample_complete_handler)() = nullptr;

	ADC(ADC_HandleTypeDef * hadc, TIM_HandleTypeDef * htim=nullptr) : hadc(hadc), htim(htim) {}

	inline void start_conversion_dma(uint16_t* buffer, uint32_t len) {
		busy = true;
		HAL_ADC_Start_DMA(hadc, (uint32_t*)buffer, len);
	}

	inline void timer_start(){
		HAL_TIM_Base_Start(htim);
	}

	inline void timer_stop(){
		HAL_TIM_Base_Stop(htim);
	}


	void interrupt_handler(){
		busy = false;
		if(sample_complete_handler != nullptr) sample_complete_handler();
	}

private:

};

#endif
