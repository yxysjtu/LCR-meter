// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <math.h>
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
        arm_sin_cos_f32(phase_acc, &pSinVal, &pCosVal);
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
float adc0_phase, adc1_phase;
float phase_diff;
void calc_amp_phase(int16_t* adc0, int16_t* adc1, uint32_t freq){
    float sin_val, cos_val;
    calc_IQ(adc0, freq);
    sin_val = filtered_sin;
    cos_val = filtered_cos;
    arm_atan2_f32(sin_val, cos_val, &adc0_phase);
    arm_sqrt_f32(sin_val * sin_val + cos_val * cos_val, &adc0_amp);
    adc0_amp *= adc0_calibration;

    calc_IQ(adc1, freq);
    sin_val = filtered_sin;
    cos_val = filtered_cos;
    arm_atan2_f32(sin_val, cos_val, &adc1_phase);
    arm_sqrt_f32(sin_val * sin_val + cos_val * cos_val, &adc1_amp);
    adc1_amp *= adc1_calibration;

    phase_diff = (adc1_phase - adc0_phase) / PI * 180;
}
