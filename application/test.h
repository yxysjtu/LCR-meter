#include "device.h"
#include "app.h"
#include "filter.h"

//float pSinVal, pCosVal;
//float phase = 0;
//float atan_input = 0, atan_output;
int btn_state = 0;
#define SAMPLE_LEN 10000
uint16_t adc0_buffer[SAMPLE_LEN];
uint16_t adc1_buffer[SAMPLE_LEN];
bool adc_start = false;
uint32_t test_freq = 3000;

void start_measure(uint8_t *data, size_t size){
	test_freq = *(uint32_t *)data;
	ui_led[0].toggle_pin();
	adc_dut.timer_stop();
	adc_dut.start_conversion_dma(adc0_buffer, SAMPLE_LEN);
	adc_ref.start_conversion_dma(adc1_buffer, SAMPLE_LEN);
	adc_dut.timer_start();
	adc_start = true;
}

extern "C" void setup(){
	//adc_dut.read_dma(adc0_buffer, SAMPLE_LEN);
	seracc_init();
	seracc_register_handler("freq", start_measure);
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
			adc_dut.timer_stop();
			adc_dut.start_conversion_dma(adc0_buffer, SAMPLE_LEN);
			adc_ref.start_conversion_dma(adc1_buffer, SAMPLE_LEN);
			adc_dut.timer_start();
		}
	}
	if(adc_start && !adc_dut.busy){

//		calc_amp_phase((int16_t*)adc0_buffer, (int16_t*)adc1_buffer, test_freq);
//		adc_start = false;
//
		adc_start = false;
		calc_amp_phase((int16_t*)adc0_buffer, (int16_t*)adc1_buffer, test_freq);
		seracc_transmit((uint8_t*)&adc0_amp, 4);
		seracc_transmit((uint8_t*)&adc1_amp, 4);
		seracc_transmit((uint8_t*)&phase_diff, 4);

//		seracc_transmit((uint8_t*)adc0_buffer, 2 * SAMPLE_LEN);
//		seracc_transmit((uint8_t*)adc1_buffer, 2 * SAMPLE_LEN);

		ui_led[0].toggle_pin();

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
