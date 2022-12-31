#include "Hal_GPIO.h"

//********************************************************************************************
void gpio_writepin(GPIO_TypeDef *gpio, uint32_t pin, uint8_t state){
	if(state) gpio->BSRR |= (1<<pin); //set pin to high
	if(!state) gpio->BSRR |= (1<<(16+pin)); //set pin to high
}

//********************************************************************************************
void gpio_togglepin(GPIO_TypeDef *gpio, uint32_t pin){
		gpio->ODR ^= (1<<pin);
}

