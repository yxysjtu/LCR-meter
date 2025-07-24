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
uint32_t test_freq = 10000;

float R_ref = 1000;
float R, X, G, B;
float L, C, Q, D;

void start_measure(uint8_t *data, size_t size){
	test_freq = *(uint32_t *)data;
	ui_led[0].toggle_pin();
	adc_dut.timer_stop();
	adc_dut.start_conversion_dma(adc0_buffer, SAMPLE_LEN);
	adc_ref.start_conversion_dma(adc1_buffer, SAMPLE_LEN);
	adc_dut.timer_start();
	adc_start = true;
}

void calc_Z(){
	float sin_val, cos_val;
	my_sin_cos(phase_diff, &sin_val, &cos_val);
	float z_mag = R_ref * amp_div;
	float y_mag = 1 / z_mag;
	R = z_mag * cos_val;
	X = z_mag * sin_val;
	G = y_mag * cos_val;
	B = y_mag * (-sin_val);

	L = X / (2 * PI * test_freq);
	Q = X / R;
//	C = B / (2 * PI * test_freq);
//	D = B / G;
	C = 1 / X / (2 * PI * test_freq);
	D = 1 / Q;

}

extern "C" void setup(){
	//adc_dut.read_dma(adc0_buffer, SAMPLE_LEN);
	seracc_init();
	seracc_register_handler("freq", start_measure);
}


extern "C" void loop(){

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
		adc_start = false;
		calc_amp_phase((int16_t*)adc0_buffer, (int16_t*)adc1_buffer, test_freq);
		//calc_Z();
		seracc_transmit((uint8_t*)&adc0_amp, 4);
		seracc_transmit((uint8_t*)&adc1_amp, 4);
		seracc_transmit((uint8_t*)&phase_diff, 4);

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
