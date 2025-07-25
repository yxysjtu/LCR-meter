#ifndef DEVICE_H
#define DEVICE_H

#include "bsp.h"

#include "button.h"
//#include "dds.h"
//#include "eeprom.h"
//#include "lcd.h"
//#include "buzzer.h"
//#include "rotary_encoder.h"
//#include "keyboard.h"
//#include "pll.h"
//#include "pwm_dc.h"
//#include "dac_ac.h"
//

extern GPIO ui_led[4];
extern GPIO ui_sw3;
extern Button btn;

extern ADC adc_dut;
extern ADC adc_ref;

extern UART serial;

//extern DDS dds0;
//extern EEPROM eeprom;
//extern Adafruit_ST7789 lcd;
//extern Buzzer buzzer;
//extern Rotary_Encoder rotary_encoder;
//extern Keyboard keyboard;
//extern PLL pll;
//extern PWM_DC pwm_dc;
//extern DAC_AC dac_ac;

#endif
