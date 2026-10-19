/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED.h"
#include "stm32f1xx_it.h"
#include "DHT11.h"
#include "Key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
DHT11_Data_TypeDef DHT11_Data;	//DHT11模块必须的结构体
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t KeyNum = 0;					//按键键码
uint16_t Menu = 0;					//菜单ID
uint8_t Pointer = 0;				//菜单指针
uint8_t Pointer_Max = 9;			//菜单指针最大值，即菜单中内容的行数，默认为9
int8_t Speed = 0;					//电机转速，范围0~100
uint8_t Encoder_Locked_Flag = 1;	//旋转编码器旋钮是否上锁，默认上锁
uint8_t HCSR505_Flag = 1;			//人体感应是否打开，默认打开
uint8_t Hour,Min,Sec;				//定时模式需要的时间变量

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t HCSR505_Get(void);			//人体感应模块函数，有人返回0，无人返回0
void Menu_Key(void);				//菜单按键控制函数
void Menu_Show(void);				//菜单内容显示函数
void Menu_Pointer(void);			//菜单指针选中处反色
void Motor_SetSpeed(int8_t Speed);	//设定电机转速函数

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();									//OLED模块初始化
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);		//开启控制电机的PWM

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Menu_Key();		//菜单按键控制函数
	  Menu_Show();		//菜单内容显示函数
	  Menu_Pointer();	//菜单指针选中处反色
	  OLED_Update();	//OLED显示内容更新

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**
  * @brief	人体感应模块
  * @retval 感应到人返回1，未感应到返回0
  */
uint8_t HCSR505_Get(void)
{
	return HAL_GPIO_ReadPin(HCSR505_GPIO_Port, HCSR505_Pin);	//直接返回引脚状态即可
}

/**
  * @brief	菜单按键控制函数
  * @retval None
  */
void Menu_Key(void)
{
	KeyNum = Key_GetNum();	//获取按键键码

	//菜单指针移动键按下
	if(KeyNum == 1)
	{
		Pointer++;
		if(Pointer > Pointer_Max)
			Pointer = 0;
	}

	//确认键按下
	else if(KeyNum == 2)
	{
		//指针不在第一行
		if(Pointer > 0)
		{
			//进入定时模式，默认速度50
			if(Menu == 0 && Pointer == 1)
			{
				Speed = 50;
				Menu = Menu*10 + Pointer;
				Pointer = 0;
			}

			//进入手动模式，默认速度50
			else if(Menu == 0 && Pointer == 2)
			{
				Speed = 50;
				Motor_SetSpeed(Speed);
				Menu = Menu*10 + Pointer;
				Pointer = 0;
			}

			//定时模式下调整参数
			else if(Menu == 1)
			{
				//确认参数键按下
				if(Pointer == 5)
				{
					HAL_TIM_Base_Start_IT(&htim3);	//启动定时
					Motor_SetSpeed(Speed);			//设定转速
					Menu = Menu*10 + Pointer;		//菜单跳转
					Pointer = 0;					//指针默认在第一行，即选中返回键
				}
			}

			//开关人体感应功能
			else if(Menu == 3 && Pointer == 3)
			{
				if(HCSR505_Flag == 1)
					HCSR505_Flag = 0;
				else
					HCSR505_Flag = 1;
			}

			//其余情况，菜单正常跳转
			else if(Menu < 1000)
			{
				Menu = Menu*10 + Pointer;
				Pointer = 0;
			}
		}

		//指针在第一行，即返回键按下
		else if(Pointer == 0)
		{
			Menu = Menu / 10;				//返回上一级菜单
			Speed = 0;						//转速归零
			Motor_SetSpeed(Speed);
			Encoder_Locked_Flag = 1;		//默认上锁旋钮
			Hour = 0;Min = 0;Sec = 0;		//定时参数归零
			HAL_TIM_Base_Stop_IT(&htim3);	//关闭定时模式的定时器
		}
	}

	//旋转编码器按键按下
	else if(KeyNum == 3)
	{
		//仅在手动模式下生效
		if(Menu == 2)
		{
			//反转即可
			if(Encoder_Locked_Flag == 0)
			{
				Encoder_Locked_Flag = 1;
			}
			else if(Encoder_Locked_Flag == 1)
			{
				Encoder_Locked_Flag = 0;
			}
		}
	}
}

/**
  * @brief	菜单内容显示函数
  * @retval None
  */
void Menu_Show(void)
{
	//主菜单内容
	if(Menu == 0)
	{
		Pointer_Max = 3;

		OLED_Clear();
		OLED_ShowChinese(39,0,"主菜单");

		OLED_ShowChinese(0,16,"定时模式");
		OLED_ShowChinese(0,32,"手动模式");
		OLED_ShowChinese(0,48,"自动模式");
	}

	//定时模式调整参数
	else if(Menu == 1)
	{
		Pointer_Max = 5;
		OLED_Clear();
		OLED_ShowChinese(0,0,"返回");

		//调整小时
		if(Pointer == 1)
		{
			Hour += Encoder_Get();
			if(Hour > 60)
				Hour = 0;
		}
		//调整分钟
		else if(Pointer == 2)
		{
			Min += Encoder_Get();
			if(Min > 60)
				Min = 0;
		}
		//调整秒
		else if(Pointer == 3)
		{
			Sec += Encoder_Get();
			if(Sec > 60)
				Sec = 0;
		}
		//调整转速
		else if(Pointer == 4)
		{
			Speed += Encoder_Get();
			if(Speed <= 0)
			{
				Speed = 0;
			}
			if(Speed >= 100)
			{
				Speed=100;
			}
		}

		//内容显示
		if(Pointer <= 3)
		{
			OLED_ShowChinese(0,16,"设置小时：");
			OLED_ShowNum(80, 16, Hour, 2, OLED_8X16);

			OLED_ShowChinese(0,32,"设置分钟：");
			OLED_ShowNum(80, 32, Min, 2, OLED_8X16);

			OLED_ShowChinese(0,48,"设置秒：");
			OLED_ShowNum(80, 48, Sec, 2, OLED_8X16);
		}
		else
		{
			OLED_ShowChinese(0,16,"设置转速：");
			OLED_ShowNum(80, 16, Speed, 3, OLED_8X16);

			OLED_ShowChinese(0,32,"确定");
		}
	}

	//定时模式倒计时界面
	else if(Menu == 15)
	{
		Pointer_Max = 0;
		OLED_Clear();
		OLED_ShowChinese(0,0,"返回");

		OLED_ShowChinese(0,16,"剩余时间：");
		OLED_Printf(0,32,OLED_8X16,"%02d:%02d:%02d",Hour,Min,Sec);

		OLED_ShowChinese(0, 48, "转速：");
		OLED_Printf(48, 48, OLED_8X16, "%d",Speed);
	}

	//手动模式
	else if(Menu == 2)
	{
		Pointer_Max = 0;
		OLED_Clear();
		OLED_ShowChinese(0,0,"返回");

		if(Encoder_Locked_Flag == 0)
		{
			Speed += Encoder_Get();
			if(Speed <= 0)
			{
				Speed = 0;
			}
			if(Speed >= 100)
			{
				Speed=100;
			}
			Motor_SetSpeed(Speed);
			OLED_ShowChinese(0, 48, "旋钮可调");
		}
		else
		{
			OLED_ShowChinese(0, 48, "旋钮锁定");
		}


		OLED_ShowChinese(0, 32, "转速：");
		OLED_Printf(48, 32, OLED_8X16, "%d",Speed);
	}

	//自动模式选择温度或湿度控制，开关人体感应功能
	else if(Menu == 3)
	{
		Pointer_Max = 3;
		OLED_Clear();
		OLED_ShowChinese(0,0,"返回");

		OLED_ShowChinese(0, 16, "温度控制");
		OLED_ShowChinese(0, 32, "湿度控制");

		if(HCSR505_Flag == 1)
			OLED_ShowChinese(0, 48, "人体感应：开");
		else
			OLED_ShowChinese(0, 48, "人体感应：关");
	}

	//自动模式温度控制
	else if(Menu == 31)
	{
		Pointer_Max = 0;
		OLED_Clear();
		OLED_ShowChinese(0,0,"返回");

		//DHT11读取数据成功
		if(DHT11_Read(&DHT11_Data) == HAL_OK)
		{
			//人体感应功能为开
			if(HCSR505_Flag == 1)
			{
				//人体感应模块感应到人
				if(HCSR505_Get() == 1)
				{
					//温度大于15摄氏度，才设定对应转速
					if(DHT11_Data.temp_int > 15)
					{
						Speed = DHT11_Data.temp_int * 3 - 12;
						if(Speed > 100)
						{
							Speed = 100;
						}
						OLED_ShowChinese(0, 16, "周围有人");
					}
					//温度过低
					else
					{
						Speed = 0;
						OLED_ShowChinese(0, 16, "温度过低");
					}
				}
				//人体感应模块未感应到人
				else
				{
					Speed = 0;
				}
			}

			//人体感应功能为关
			else
			{
				//温度大于15摄氏度，才设定对应转速
				if(DHT11_Data.temp_int > 15)
				{
					Speed = DHT11_Data.temp_int * 3 - 12;
					if(Speed > 100)
					{
						Speed = 100;
					}
				}
				//温度过低
				else
				{
					Speed = 0;
					OLED_ShowChinese(0, 16, "温度过低");
				}
			}

			Motor_SetSpeed(Speed);
			OLED_ShowChinese(0, 32, "温度：");
			OLED_Printf(48, 32, OLED_8X16, "%d.%d", DHT11_Data.temp_int, DHT11_Data.temp_deci);
		}

		OLED_ShowChinese(0, 48, "转速：");
		OLED_Printf(48, 48, OLED_8X16, "%d",Speed);
	}

	//自动模式湿度控制
	else if(Menu == 32)
	{
		Pointer_Max = 0;
		OLED_Clear();
		OLED_ShowChinese(0,0,"返回");

		//DHT11读取数据成功
		if(DHT11_Read(&DHT11_Data) == HAL_OK)
		{
			//人体感应功能为开
			if(HCSR505_Flag == 1)
			{
				//人体感应模块感应到人
				if(HCSR505_Get() == 1)
				{
					//湿度大于20才设定对应转速
					if(DHT11_Data.humi_int > 20)
					{
						Speed = DHT11_Data.humi_int * 1.5 - 1;
						if(Speed > 100)
						{
							Speed = 100;
						}
						OLED_ShowChinese(0, 16, "周围有人");
					}
					//湿度过低
					else
					{
						Speed = 0;
						OLED_ShowChinese(0, 16, "湿度过低");
					}
				}
				//人体感应模块未感应到人
				else
				{
					Speed = 0;
				}
			}

			//人体感应功能为关
			else
			{
				//湿度大于20才设定对应转速
				if(DHT11_Data.humi_int > 20)
				{
					Speed = DHT11_Data.humi_int * 1.5 - 1;
					if(Speed > 100)
					{
						Speed = 100;
					}
				}
				//湿度过低
				else
				{
					Speed = 0;
					OLED_ShowChinese(0, 16, "湿度过低");
				}
			}

			Motor_SetSpeed(Speed);
			OLED_ShowChinese(0, 32, "湿度：");
			OLED_Printf(48, 32, OLED_8X16, "%d.%d", DHT11_Data.humi_int, DHT11_Data.humi_deci);
		}

		OLED_ShowChinese(0, 48, "转速：");
		OLED_Printf(48, 48, OLED_8X16, "%d",Speed);
	}


	/*else if*/
	//...

	/*未定义菜单的显示内容*/
	else
	{
		Pointer_Max = 0;
		OLED_Clear();
		OLED_ShowChinese(0,0,"返回");
		OLED_Printf(32,0,OLED_8X16,"(Menu:%5d)",Menu);
		OLED_Printf(0,16,OLED_8X16,"undefined");
	}
}

/**
  * @brief	菜单指针选中区域反色
  * @retval None
  */
void Menu_Pointer(void)
{
	//“主菜单”三个字不反色
	if(Pointer == 0)
	{
		if(Menu != 0)
		{
			OLED_ReverseArea(0,0,128,16);
		}
	}
	else if(Pointer==1 || Pointer==4 || Pointer==7)
	{
		OLED_ReverseArea(0,16,128,16);
	}
	else if(Pointer==2 || Pointer==5 || Pointer==8)
	{
		OLED_ReverseArea(0,32,128,16);
	}
	else if(Pointer==3 || Pointer==6 || Pointer==9)
	{
		OLED_ReverseArea(0,48,128,16);
	}

}

/**
  * @brief	设定电机转速
  * @retval None
  */
void Motor_SetSpeed(int8_t Speed)
{
	if(Speed >= 0)
	{

		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);

		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, Speed);
	}

	else
	{
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);

		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, -Speed);
	}
}

/**
  * @brief	定时模式定时器中断函数
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)
	{
		//判断倒计时是否结束
		if(Hour==0 && Min==0 && Sec==0)
		{
			HAL_TIM_Base_Stop_IT(&htim3);	//关闭定时器
			Speed = 0;						//转速归零
			Motor_SetSpeed(Speed);
		}

		//未结束
		else
		{
			Sec--;
			if(Sec >= 60)
			{
				Min--;
				Sec = 59;
			}
			if(Min >= 60)
			{
				Hour--;
				Min = 59;
			}
		}
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
