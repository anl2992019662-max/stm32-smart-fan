/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DHT11_Pin GPIO_PIN_0
#define DHT11_GPIO_Port GPIOA
#define AIN1_Pin GPIO_PIN_4
#define AIN1_GPIO_Port GPIOA
#define AIN2_Pin GPIO_PIN_5
#define AIN2_GPIO_Port GPIOA
#define Key_1_Pin GPIO_PIN_0
#define Key_1_GPIO_Port GPIOB
#define Encoder_Key_Pin GPIO_PIN_1
#define Encoder_Key_GPIO_Port GPIOB
#define Key_2_Pin GPIO_PIN_10
#define Key_2_GPIO_Port GPIOB
#define Encoder_S2_Pin GPIO_PIN_14
#define Encoder_S2_GPIO_Port GPIOB
#define Encoder_S2_EXTI_IRQn EXTI15_10_IRQn
#define Encoder_S1_Pin GPIO_PIN_15
#define Encoder_S1_GPIO_Port GPIOB
#define Encoder_S1_EXTI_IRQn EXTI15_10_IRQn
#define HCSR505_Pin GPIO_PIN_8
#define HCSR505_GPIO_Port GPIOA
#define OLED_SCK_Pin GPIO_PIN_8
#define OLED_SCK_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
