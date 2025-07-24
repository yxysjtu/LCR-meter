// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <math.h>
#include "algorithm.h"

#define PI 3.14159265358979f
#define SIGNAL_LEN 10000

#define MAX_SECTIONS 10  // 最大支持的biquad节数，可根据需求修改

// 二阶节结构体
typedef struct {
    float b0, b1, b2;  // 分子系数
    float a1, a2;      // 分母系数（注意：a0默认为1）
    float x1, x2;      // 输入延迟 x[n-1], x[n-2]
    float y1, y2;      // 输出延迟 y[n-1], y[n-2]
    float g;
} Biquad;


// 初始化单个 biquad 节
void init_biquad(Biquad* s, float b0, float b1, float b2, float a1, float a2, float g) {
    s->b0 = b0;
    s->b1 = b1;
    s->b2 = b2;
    s->a1 = a1;
    s->a2 = a2;
    s->x1 = s->x2 = 0.0f;
    s->y1 = s->y2 = 0.0f;
    s->g = g;
}

// 对一个样本进行滤波（单个 biquad）
float process_biquad(Biquad* s, float x) {
    float y = (s->b0 * x + s->b1 * s->x1 + s->b2 * s->x2) * s->g
                    - s->a1 * s->y1 - s->a2 * s->y2;

    // 更新状态变量
    s->x2 = s->x1;
    s->x1 = x;
    s->y2 = s->y1;
    s->y1 = y;

    return y;
}

// 串联多个 biquad 节实时处理一个样本
float process_biquad_cascade(Biquad* sections, int numSections, float input) {
    float x = input;
    for (int i = 0; i < numSections; i++) {
        x = process_biquad(&sections[i], x);  // 每节依次处理
        //printf("%f\n", x);
    }
    //printf("\n");
    return x;  // 输出最终结果
}

void my_sin_cos(float phase, float *pSinVal, float *pCosVal){
	arm_sin_cos_f32(phase, pSinVal, pCosVal);
	if(*pSinVal > 1.0f || *pSinVal < -1.0f) *pSinVal = 0;
	if(*pCosVal > 1.0f || *pCosVal < -1.0f) *pCosVal = 0;
}
void filter_init(Biquad* filter, float* coeffs, float g){
    init_biquad(&filter[1], coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4], g);
    init_biquad(&filter[0], coeffs[5], coeffs[6], coeffs[7], coeffs[8], coeffs[9], g);
}

Biquad filter_sin[2];
Biquad filter_cos[2];
float coeffs[10] = {
        1.0f, 1.0f, 0.0f, -0.993736471541615f, 0.0f,
        1.0000f, 2.0000f, 1.0000f, -1.993697178514108f, 0.993736533166361f
    };
float g = 1.755345351901828e-04;

float channel_sin, channel_cos;
float filtered_sin, filtered_cos;
//计算通道IQ分量
void calc_IQ(int16_t* adc, uint32_t freq){
    float mean = 0;
    float phase_acc = 0;
    float phase_delta = 360.0 * (float)freq / 1000000;
    float pSinVal;
    float pCosVal;

    for(int i = 0; i < SIGNAL_LEN; i++){
        mean += adc[i];
    }
    mean /= SIGNAL_LEN;

    filter_init(filter_sin, coeffs, g);
    filter_init(filter_cos, coeffs, g);
    for(int i = 0; i < SIGNAL_LEN; i++){
    	my_sin_cos(phase_acc, &pSinVal, &pCosVal);
        phase_acc += phase_delta;
        if(phase_acc >= 360) phase_acc -= 360;
        channel_sin = ((float)adc[i] - mean) * pSinVal;
        channel_cos = ((float)adc[i] - mean) * pCosVal;
        filtered_sin = process_biquad_cascade(filter_sin, 2, channel_sin);//filter(channel_sin, x_sin, y_sin);
        filtered_cos = process_biquad_cascade(filter_cos, 2, channel_cos);//filter(channel_cos, x_cos, y_cos);
        //printf("%f\t%f\n", channel_sin, channel_cos);
        //printf("%f\t%f\n", filtered_sin, filtered_cos);
    }

}

float adc0_calibration = 1, adc1_calibration = 1;
float adc0_amp, adc1_amp;
float adc0_amp_cali, adc1_amp_cali;
float adc0_phase, adc1_phase;
float phase_diff;

const float amp0_10k[] = {
    31.4021912f, 63.4520874f, 94.8571701f, 126.065697f, 157.232208f, 188.593307f, 219.772369f, 251.12854f,
    282.435608f, 313.594299f, 344.81246f, 375.86624f, 406.88117f, 437.81351f, 468.80991f,
    499.89253f, 530.96039f, 561.99588f, 593.12665f, 624.21668f
};

const float amp1_10k[] = {
    31.8198833f, 64.8770142f, 96.2158279f, 127.33445f, 158.225449f, 189.43782f, 220.383667f, 251.488251f,
    282.568878f, 313.524475f, 344.61911f, 375.49823f, 406.35849f, 437.06067f, 467.86954f,
    498.72351f, 529.48475f, 560.41064f, 591.32440f, 622.19748f
};

//amp0_10k: y ≈ 0.31162728 * x + 1.43679743
//amp1_10k: y ≈ 0.30984957 * x + 3.12907649
float amp0_k = 3.20894365, amp0_b = -4.60471254;
float amp1_k = 3.22732929, amp1_b = -10.08448801;

float calibrate_amp(const float* amp_ref, float amp, float k, float b){
	int n = 20;
	int index = amp / amp_ref[0];
	if(index < 1 || index >= 20){
		return k * amp + b;
	}
	//线性插值
	return (amp - amp_ref[index - 1]) / (amp_ref[index] - amp_ref[index - 1]) * 100 + (index * 100);
}

//float phase_10k = {};
//float phase_200mV = {};
//float phase_700mV = {};
//float phase_out;
//
//float interp(float val1, float val2, float k){
//	return (val2 - val1) * k + val1;
//}
//
//float calibrate_phase(float* cali1, float* cali2, float* cali3, uint32_t freq, float val){
//	float y11 = cali1[1];
//	float y12 = cali1[9];
//	int freq_index = freq / 10000;
//	float y21 = interp(cali2[freq_index - 1], cali2[freq_index], ((float)freq - freq_index * 10000) / 10000);
//	float y22 = interp(cali3[freq_index - 1], cali3[freq_index], ((float)freq - freq_index * 10000) / 10000);
//    float k = (y22-y21) / (y12-y11);
//    float b = y21 - k * y11;
//    int val_index = amp / 100;
//    float phase_ref = interp(cali1[val_index - 1], cali1[val_index],((float)val - val_index * 100) / 100 );
//
//    return (k * phase_ref) + b;
//}

float p1, p2;
void calc_amp_phase(int16_t* adc0, int16_t* adc1, uint32_t freq){
    float sin_val, cos_val;
    calc_IQ(adc0, freq);
    sin_val = filtered_sin;
    cos_val = filtered_cos;
    arm_atan2_f32(sin_val, cos_val, &adc0_phase);
    arm_sqrt_f32(sin_val * sin_val + cos_val * cos_val, &adc0_amp);
    adc0_amp *= 3.1847;
//    adc0_amp_cali = calibrate_amp(amp0_10k, adc0_amp, amp0_k, amp0_b);

    calc_IQ(adc1, freq);
    sin_val = filtered_sin;
    cos_val = filtered_cos;
    arm_atan2_f32(sin_val, cos_val, &adc1_phase);
    arm_sqrt_f32(sin_val * sin_val + cos_val * cos_val, &adc1_amp);
    adc1_amp *= 3.1847;
//    adc1_amp_cali = calibrate_amp(amp1_10k, adc1_amp, amp1_k, amp1_b);

    phase_diff = (adc1_phase - adc0_phase) / PI * 180;
//    amp_div = adc0_amp / adc1_amp;

}
