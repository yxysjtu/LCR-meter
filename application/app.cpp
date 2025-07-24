#include "device.h"
#include "app.h"
#include "filter.h"


#define SAMPLE_LEN 10000
uint16_t adc0_buffer[SAMPLE_LEN];
uint16_t adc1_buffer[SAMPLE_LEN];
uint32_t test_freq = 10000;
int measure_state = 0;

float V_dut, V_ref;
float V_div;

float R_ref = 1000;
float dut_gain = 1;

float R, X, G, B;
float L, C_s, Q, D;
float C_p;

void start_measure(uint8_t *data, size_t size){
	test_freq = *(uint32_t *)data;
	ui_led[0].toggle_pin();
	adc_dut.timer_stop();
	adc_dut.start_conversion_dma(adc0_buffer, SAMPLE_LEN);
	adc_ref.start_conversion_dma(adc1_buffer, SAMPLE_LEN);
	adc_dut.timer_start();

	measure_state = 1;
}

void get_V(){
	V_ref = adc1_amp;
	V_dut = adc0_amp / dut_gain;
	V_div = V_dut / V_ref;
}

void calc_Z(){
	float sin_val, cos_val;
	my_sin_cos(phase_diff, &sin_val, &cos_val);
	float z_mag = R_ref * V_div;
	float y_mag = 1 / z_mag;
	R = z_mag * cos_val;
	X = z_mag * sin_val;
	G = y_mag * cos_val;
	B = y_mag * (-sin_val);

	L = X / (2 * PI * test_freq);
	Q = X / R;
	C_p = B / (2 * PI * test_freq);
//	D = B / G;
	C_s = 1 / X / (2 * PI * test_freq);
	D = 1 / Q;

}

extern "C" void setup(){
	//adc_dut.read_dma(adc0_buffer, SAMPLE_LEN);
	seracc_init();
	seracc_register_handler("freq", start_measure);
}



extern "C" void loop(){
	switch(measure_state){
		case 0:{//等待被触发
			if(btn.get_pressed_state()){
				if(!adc_dut.busy && !adc_ref.busy){
					ui_led[0].toggle_pin();
					adc_dut.timer_stop();
					adc_dut.start_conversion_dma(adc0_buffer, SAMPLE_LEN);
					adc_ref.start_conversion_dma(adc1_buffer, SAMPLE_LEN);
					adc_dut.timer_start();

					measure_state = 1;
				}
			}
		}break;
		case 1:{
			if(!adc_dut.busy){
				ui_led[0].toggle_pin();
				calc_amp_phase((int16_t*)adc0_buffer, (int16_t*)adc1_buffer, test_freq);
				get_V();
				//根据幅度和频率进行估计，调整参考电阻和pga

				//下一次测量
				ui_led[0].toggle_pin();
				adc_dut.timer_stop();
				adc_dut.start_conversion_dma(adc0_buffer, SAMPLE_LEN);
				adc_ref.start_conversion_dma(adc1_buffer, SAMPLE_LEN);
				adc_dut.timer_start();

				measure_state = 2;
			}
		}break;
		case 2:{
			if(!adc_dut.busy){
				ui_led[0].toggle_pin();
				calc_amp_phase((int16_t*)adc0_buffer, (int16_t*)adc1_buffer, test_freq);
				get_V();
				calc_Z();
				//发送给上位机

				measure_state = 0;
			}
		}break;
	}

//	if(btn.get_pressed_state()){
//		if(!adc_dut.busy && !adc_ref.busy){
//			adc_start = true;
//			ui_led[0].toggle_pin();
//			adc_dut.timer_stop();
//			adc_dut.start_conversion_dma(adc0_buffer, SAMPLE_LEN);
//			adc_ref.start_conversion_dma(adc1_buffer, SAMPLE_LEN);
//			adc_dut.timer_start();
//		}
//	}
//	if(adc_start && !adc_dut.busy){
//		adc_start = false;
//		calc_amp_phase((int16_t*)adc0_buffer, (int16_t*)adc1_buffer, test_freq);
//		get_V();
//		seracc_transmit((uint8_t*)&adc0_amp, 4);
//		seracc_transmit((uint8_t*)&adc1_amp, 4);
//		seracc_transmit((uint8_t*)&phase_diff, 4);
//
//		ui_led[0].toggle_pin();
//
//	}

}

uint32_t tick = 0;
extern "C" void task_handler(){
	tick = HAL_GetTick();


	if(tick % 500 == 0){
		ui_led[1].toggle_pin();
	}
	btn.task_handler();
	relay1.task_handler();
	relay2.task_handler();
	relay3.task_handler();
	relay4.task_handler();
	relay5.task_handler();
	relay6.task_handler();
}
