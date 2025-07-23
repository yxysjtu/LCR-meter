#include "device.h"
#include "app.h"
#include "algorithm.h"

//float pSinVal, pCosVal;
//float phase = 0;
//float atan_input = 0, atan_output;
int btn_state = 0;
#define SAMPLE_LEN 10000
uint16_t adc0_buffer[SAMPLE_LEN];
uint16_t adc1_buffer[SAMPLE_LEN];
bool adc_start = false;

extern "C" void setup(){
	dds.set_freq(1 * 1e6f);
	adc_dut.read_dma(adc0_buffer, SAMPLE_LEN);
	seracc_init();
}


extern "C" void loop(){
//	arm_sin_cos_f32(phase, &pSinVal, &pCosVal);
//	arm_atan2_f32(atan_input, 1, &atan_output);
//	ui_led[0].toggle_pin();
//	HAL_Delay(500);
//	ui_led[0].set_pin(ui_sw3.read_pin());
//	btn_state = ui_sw3.read_pin();
//	if(btn.get_pressed_state()) ui_led[0].toggle_pin();


	if(btn.get_pressed_state()){
		if(!adc_dut.busy && !adc_ref.busy){
			adc_start = true;
			ui_led[0].toggle_pin();
			adc_dut.read_dma(adc0_buffer, SAMPLE_LEN);
			adc_ref.read_dma(adc1_buffer, SAMPLE_LEN);
			//HAL_TIM_Base_Start(&htim6);
		}
	}
	if(adc_start && !adc_dut.busy){
//		for(int i = 0; i < SAMPLE_LEN; i++){
//			serial.write(adc0_buffer[i] >> 8);
//			serial.write(adc0_buffer[i] && 0xff);
//		}

		calc_amp_phase((int16_t*)adc0_buffer, (int16_t*)adc1_buffer, 100000);
		adc_start = false;

	}

}

uint32_t tick = 0;
extern "C" void task_handler(){
	tick = HAL_GetTick();


	if(tick % 500 == 0){
		ui_led[1].toggle_pin();
	}
	btn.task_handler();
}
