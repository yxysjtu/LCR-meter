#include "device.h"

GPIO ui_led[4] = {GPIO(UI_LED0_GPIO_Port, UI_LED0_Pin),
		GPIO(UI_LED1_GPIO_Port, UI_LED1_Pin),
		GPIO(UI_LED2_GPIO_Port, UI_LED2_Pin),
		GPIO(UI_LED3_GPIO_Port, UI_LED3_Pin)};

GPIO ui_sw3(UI_SW3_GPIO_Port, UI_SW3_Pin);
Button btn(ui_sw3, true);

ADC adc_dut(&hadc1);
ADC adc_ref(&hadc2);

UART serial(&huart5);

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(hadc == adc_dut.hadc){
		adc_dut.interrupt_handler();
		//HAL_TIM_Base_Stop(&htim6);
	}
	if(hadc == adc_ref.hadc){
		adc_ref.interrupt_handler();
		//HAL_TIM_Base_Stop(&htim6);
	}
}
