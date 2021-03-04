#include "main.h"             // Device header

int main(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;//Включает такртирование порта B
	GPIOB->OSPEEDR |= 0x00005555;
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 
								| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER7_0 
								| GPIO_MODER_MODER6_0 | GPIO_MODER_MODER5_0 
								| GPIO_MODER_MODER4_0	|  GPIO_MODER_MODER3_0 
								| GPIO_MODER_MODER8_0;
	GPIOB->MODER&=~( GPIO_MODER_MODER12 | GPIO_MODER_MODER13 |  GPIO_MODER_MODER14 |  GPIO_MODER_MODER15);
	
	unsigned  reg[8] = {0x101, 0x002, 0x004, 0x080, 0x040, 0x020, 0x010, 0x008};  
	uint32_t n;

	while(1){
		
		n=((GPIOB->IDR)&0x3000)>>12;

		if( ((GPIOB->IDR)&0x4000)>>14 != 1){
			if( ((GPIOB->IDR)&0x8000)>>15 != 1){
				for (uint32_t i = 0; i<9; i++){
					GPIOB->ODR |= reg[i];
					delay((uint32_t)50000<<n);
				}		
				for (uint32_t j = 0; j<9; j++){
					GPIOB->ODR &=~ reg[j];
					delay((uint32_t)50000<<n);
				}
			}
			else{
				for (uint32_t i = 0; i<9; i++){
					GPIOB->ODR |= reg[i];
					delay((uint32_t)50000<<n);
					GPIOB->ODR &=~ reg[i];		
				}	
			}
		}
		
		else{
			if( ((GPIOB->IDR)&0x8000)>>15 != 1){
				for (int i = 8; i>=0; i--){
					GPIOB->ODR |= reg[i];
					delay((uint32_t)50000<<n);
				}		
				for (int j = 8; j>=0; j--){
					GPIOB->ODR &=~ reg[j];
					delay((uint32_t)50000<<n);
				}
			}
			else{
				for (int i = 8; i>=0; i--){
					GPIOB->ODR |= reg[i];
					delay((uint32_t)50000<<n);
					GPIOB->ODR &=~ reg[i];		
				}	
			}			
		}	
	}
		
}

void delay(uint32_t count)
{
	volatile uint32_t i;
	for (i =0;i<count;i++);
}
