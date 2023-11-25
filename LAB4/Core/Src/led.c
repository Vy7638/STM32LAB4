/*
 * led.c
 *
 *  Created on: Nov 23, 2023
 *      Author: ADMIN
 */

#include "led.h"

void blinkyLed1(void){
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}
void blinkyLed2(void){
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}
void blinkyLed3(void){
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}
void blinkyLed4(void){
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}
void blinkyLed5(void){
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}
