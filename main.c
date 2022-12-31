#include "stm32f4xx.h"
#include "Hal_GPIO.h"

void Init_Delay(void);

void TIM4_IRQHandler(void);

uint32_t myticks = 0;

void dUs(uint32_t us);
void dMs(uint32_t ms);

int main(void){
	//Speed control for Motor A and Motor B
	//PWM on two pins 
	//PB8 - TIM10
	//PB9 - TIM11
	
	//Initialize clocks for GPIOA, GPIOB and GPIOC
	RCC->AHB1ENR |= ( (1<<0) | (1<<1) | (1<<2));
	//Timer 10 and Timer 11
	RCC-> APB2ENR |= ( (1<<17) | (1<<18) );
	//Timer 4
	RCC->AHB2ENR |= RCC_APB1ENR_TIM4EN;
	
	Init_Delay();
	//Timers and Calculations
	// Sysclock speed is 16MHz or or 16000KHz, 16000000Hz
	// Timer 10 Channel 1
	
	//PWM MODE 
	TIM10->CCMR1 |= ( (1<<6) | (1<<5) | (0<<4) ); //PWM MODE 1
	TIM10->CCMR1 |= (1<<3); //Preload Enable 
	TIM10->CR1 |= (1<<7); // ARPE
	
	TIM10->PSC = 16;
	TIM10->ARR = 1000;
	TIM10->CCR1 = 250;
	 
	TIM10->EGR |= (1<<0); // Event generation
	TIM10->CCER |= ( (0<<1) | (0<<0) ); //Output polarity | Output enable
	TIM10->CR1 |= (1<<0); // Enable Counter
	
	//Timer 11 Channel 1
	//PWM MODE
	TIM11->CCMR1 |=  ( (1<<6) | (1<<5) | (0<<4) ); //PWM MODE 1
	TIM11->CCMR1 |= (1<<3); //Preload Enable
	TIM11->CCMR1 |= (1<<2);
	TIM11->CR1 |= (1<<7);
	
	TIM11->PSC = 8;
	TIM11->ARR = 2000;
	TIM11->CCR1 = 1500;
	
	TIM11->EGR |= (1<<0); //Event generation
	TIM11->CCER |= ( (0<<1) | (1<<0) );//Output polarity | Output enable
	TIM11->CR1 |= (1<<0); // ARPE| Enable Counter
	
	// GPIO PINS
	//PA3
	GPIOA->MODER |= ( (0<<7) | (0<<6) ); //Input Function
	GPIOA->OTYPER |= (0<<3); // Output push pull
	GPIOA->OSPEEDR |= ( (0<<7) | (1<<6) ); // Medium Speed
	GPIOA->PUPDR |= ( (0<<7) | (1<<6) ); // Pull up
	
	//PB8
	GPIOB->MODER |= ( (1<<17) | (0<<16)); //Alternate function for timer
	GPIOB->OTYPER |= (0<<8); // Output push pull
	GPIOB->OSPEEDR |= ( (1<<17) | (1<<16)); // Very High Speed
	GPIOB->PUPDR |= ( (0<<17) | (0<<16) ); // Pull up
	GPIOB->AFR[1] |= ( (0<<3) | (0<<2) | (1<<1) | (1<<0) ); // Alternate function to be used Timer 10. Reference datasheet.
	
	//PB9
	GPIOB->MODER |= ( (1<<19) | (0<<18) ); // Alternate function for timer
	GPIOB->OTYPER |= (0<<9); // Output push pull
	GPIOB->OSPEEDR |=( (1<<19) | (1<<18) ); // Very High Speed
	GPIOB->PUPDR |= ( (0<<19) | (0<<18) ); // Pull Up
	GPIOB->AFR[1] |= ( (0<<7) | (0<<6) | (1<<5) | (1<<4) ); // Alternate function to be used Timer 11. Reference datasheet

	//PC13 // Led PIN
	GPIOC->MODER |= ( (0<<27) | (1<<26) ); //Output Function
	GPIOC->OTYPER |= (0<<13); // Output push pull
	GPIOC->OSPEEDR |= ( (0<<27) | (0<<26) ); // Low Speed
	GPIOC->PUPDR |= ( (0<<27) | (1<<26) ); // Pull up
	
	while(1){
		dUs(4000);
	}
}


void Init_Delay(void){
	//TIM4 CH1
	TIM4->PSC = 0;
	TIM4->ARR = 16;
	TIM4->CR1 |= (1<<2); // Only counter overflow calls interrupt::::URS
	TIM4->DIER |= (1<<0); // Enable update interrupt :::: UIE 
	TIM4->EGR |= (1<<0); // Gennerate event :::: UG
	//TIM4->CR1 |= (1<<0); //ENable Counter
	
	NVIC_EnableIRQ(TIM4_IRQn);
}

void TIM4_IRQHandler(void){
	//Check what generated interrupt using SR
	/*if(TIM4->SR & TIM4_SR_UIF){
	
	}*/
	myticks++;
	TIM4->SR &= ~TIM_SR_UIF;
}

void dUs(uint32_t us){
	TIM4->CR1 |= TIM_CR1_CEN;
	myticks = 0;
	
	while(myticks < us);
	TIM4->CR1 &= ~TIM_CR1_CEN;
	
}

void dMs(uint32_t ms){
	TIM4->CR1 |= TIM_CR1_CEN;
	myticks = 0;
	
	while(myticks < ms);
	TIM4->CR1 &= ~TIM_CR1_CEN;
	
}
