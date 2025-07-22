#ifndef GPIO_H
#define GPIO_H

#include "driver.h"


class GPIO{
public:
	GPIO_TypeDef * gpio;
	uint16_t pin;

    GPIO(GPIO_TypeDef * gpio=nullptr, uint16_t pin=0) : gpio(gpio), pin(pin) {}

    inline void set_pin(uint8_t level){
        if(level) HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
        else HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
    }

    inline void toggle_pin(){
    	HAL_GPIO_TogglePin(gpio, pin);
    }

    bool read_pin(){
        return (bool)(HAL_GPIO_ReadPin(gpio, pin));
    }

};


#endif
