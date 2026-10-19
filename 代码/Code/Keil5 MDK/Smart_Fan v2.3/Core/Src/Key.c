#include "main.h"

uint8_t Key_GetNum(void)
{
	uint8_t Key_Temp = 0;
	volatile int i;

	if(HAL_GPIO_ReadPin(Key_1_GPIO_Port, Key_1_Pin) == GPIO_PIN_RESET)
	{
        for (i = 0; i < 100000; i++) {}
		while(HAL_GPIO_ReadPin(Key_1_GPIO_Port, Key_1_Pin) == GPIO_PIN_RESET);
        for (i = 0; i < 100000; i++) {}
		Key_Temp = 1;
	}
	else if(HAL_GPIO_ReadPin(Key_2_GPIO_Port, Key_2_Pin) == GPIO_PIN_RESET)
	{
        for (i = 0; i < 100000; i++) {}
		while(HAL_GPIO_ReadPin(Key_2_GPIO_Port, Key_2_Pin) == GPIO_PIN_RESET);
        for (i = 0; i < 100000; i++) {}
		Key_Temp = 2;
	}
	else if(HAL_GPIO_ReadPin(Encoder_Key_GPIO_Port, Encoder_Key_Pin) == GPIO_PIN_RESET)
	{
		for (i = 0; i < 100000; i++) {}
		while(HAL_GPIO_ReadPin(Encoder_Key_GPIO_Port, Encoder_Key_Pin) == GPIO_PIN_RESET);
		for (i = 0; i < 100000; i++) {}
		Key_Temp = 3;
	}

	return Key_Temp;
}
