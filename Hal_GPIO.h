#ifndef HAL_GPIO
#define HAL_GPIO

#include "stm32f4xx.h"


#define SET_LOW				0
#define SET_HIGH			1

//PORT NAMES
#define PORTA			GPIOA
#define PORTB			GPIOB
#define PORTC			GPIOC

//PIN MODE
#define INPUT					((uint32_t) 0x00)
#define OUTPUT				((uint32_c) 0x01)
#define ALTERNATE			((uint32_t) 0x02)
#define ANALOG				((uint32_t) 0x03)

//OUTPUT TYPE
#define PUSH_PULL				((uint32_t) 0x00) 
#define OPEN_DRAIN			((uint32_t) 0x01)

//OUTPUT SPEED
#define LOW						((uint32_t) 0x00)
#define MEDIUM				((uint32_t) 0x01)		
#define HIGH					((uint32_t) 0x02)
#define VERY_HIGH			((uint32_t) 0x03)

//PULLUP/PULLDOWN
#define NO_PULL				((uint32_t) 0x00)
#define PULL_UP				((uint32_t) 0x01)
#define PULL_DOWN			((uint32_t) 0x02)
#define RESERVED			((uint32_t) 0x03)

//CLOCK INIT
#define GPIOA_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<0));
#define GPIOB_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<1));
#define GPIOC_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<2));
#define GPIOD_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<3));

struct pinStruct{
	uint32_t pin;
	uint32_t moder;
	uint32_t type;
	uint32_t speed;
	uint32_t pull;
};

void gpio_writepin(GPIO_TypeDef *gpio, uint32_t pin, uint8_t state);

void gpio_togglepin(GPIO_TypeDef *gpio, uint32_t pin);

#endif