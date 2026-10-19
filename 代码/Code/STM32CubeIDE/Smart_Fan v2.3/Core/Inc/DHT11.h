#ifndef _DHT11_H
#define _DHT11_H

#include "main.h"

#define	HIGH  		1
#define LOW   		0
#define DHT11_OK	0
#define DHT11_ERROR	1

typedef struct
{
    uint8_t  humi_int;       // 湿度的整数部分
    uint8_t  humi_deci;      // 湿度的小数部分
    uint8_t  temp_int;       // 温度的整数部分
    uint8_t  temp_deci;      // 温度的小数部分
    uint8_t  check_sum;      // 校验和

} DHT11_Data_TypeDef;

void DHT11_Init(void);
uint8_t DHT11_Read(DHT11_Data_TypeDef *DHT11_Data);

#endif
