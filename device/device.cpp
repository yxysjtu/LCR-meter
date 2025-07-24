#include "device.h"

GPIO ui_led[4] = {GPIO(UI_LED0_GPIO_Port, UI_LED0_Pin),
		GPIO(UI_LED1_GPIO_Port, UI_LED1_Pin),
		GPIO(UI_LED2_GPIO_Port, UI_LED2_Pin),
		GPIO(UI_LED3_GPIO_Port, UI_LED3_Pin)};

GPIO ui_sw3(UI_SW3_GPIO_Port, UI_SW3_Pin);
Button btn(ui_sw3, true);

ADC adc_dut(&hadc1, &htim6);
ADC adc_ref(&hadc2, &htim6);

UART serial(&huart5);

SPI AD9834_spi(&hspi4);
AD9834 dds(AD9834_spi,25);

GPIO s1(RELAY1_S_GPIO_Port, RELAY1_S_Pin);
GPIO r1(RELAY1_R_GPIO_Port, RELAY1_R_Pin);
Relay relay1(s1,r1);

GPIO s2(RELAY2_S_GPIO_Port, RELAY2_S_Pin);
GPIO r2(RELAY2_R_GPIO_Port, RELAY2_R_Pin);
Relay relay2(s2,r2);

GPIO s3(RELAY3_S_GPIO_Port, RELAY3_S_Pin);
GPIO r3(RELAY3_R_GPIO_Port, RELAY3_R_Pin);
Relay relay3(s3,r3);

GPIO s4(RELAY4_S_GPIO_Port, RELAY4_S_Pin);
GPIO r4(RELAY4_R_GPIO_Port, RELAY4_R_Pin);
Relay relay4(s4,r4);

GPIO s5(RELAY5_S_GPIO_Port, RELAY5_S_Pin);
GPIO r5(RELAY5_R_GPIO_Port, RELAY5_R_Pin);
Relay relay5(s5,r5);

GPIO s6(RELAY6_S_GPIO_Port, RELAY6_S_Pin);
GPIO r6(RELAY6_R_GPIO_Port, RELAY6_R_Pin);
Relay relay6(s6,r6);




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
