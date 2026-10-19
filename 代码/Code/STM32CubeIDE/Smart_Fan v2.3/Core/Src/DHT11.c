#include "DHT11.h"

/*
DHT11数据手册：
http://www.aosong.com/userfiles/files/media/DHT11-V1_3%E8%AF%B4%E6%98%8E%E4%B9%A6%EF%BC%88%E8%AF%A6%E7%BB%86%E7%89%88%EF%BC%89.pdf

主函数需要定义对应结构体：
DHT11_Data_TypeDef DHT11_Data;
主函数需要调用DHT11初始化函数：
DHT11_Init();
主函数调用读取DHT11温湿度时的语句，执行后温湿度数据写入对应结构体中
DHT11_Read(&DHT11_Data)
*/


/*
 * 函数	微秒级延时
 * 参数	xus 延时时长，范围：0~233015
 * 返回	无
 */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/*
 * 函数	毫秒级延时
 * 参数	xms 延时时长，范围：0~4294967295
 * 返回	无
 */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}

/*
 * 函数	给DHT11的DATA引脚输出高电平或低电平
 * 参数	HIGH或者LOW
 * 返回	无
 */
void DHT11_DATA_OUT(GPIO_PinState DATA)
{
	if(DATA)
		HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET);
}

/*
 * 函数	读取DHT11的DATA引脚电平
 * 参数	无
 * 返回	DHT11的DATA引脚电平
 */
GPIO_PinState DHT11_DATA_IN(void)
{
	return HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin);
}

/*
 * 函数	DHT11初始化，将DATA引脚拉高
 * 参数	无
 * 返回	无
 */
void DHT11_Init(void)
{
    // 设置初始状态
    HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET);
}

/*
 * 函数	配置STM32的DHT11引脚为上拉输入模式
 * 参数	无
 * 返回	无
 */
void DHT11_Mode_IPU(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = DHT11_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

/*
 * 函数	配置STM32的DHT11引脚为推挽输出模式
 * 参数	无
 * 返回	无
 */
void DHT11_Mode_Out_PP(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = DHT11_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

/*
 * 函数	DHT11通信起始信号
 * 参数	无
 * 返回	无
 * 说明	DATA引脚在高电平状态下被拉低20ms后拉高13us，即为起始信号
 */
void DHT11_Start(void)
{
    DHT11_Mode_Out_PP();
    DHT11_DATA_OUT(LOW);
    Delay_ms(20);
    DHT11_DATA_OUT(HIGH);
    Delay_us(13);
}

/*
 * 函数	读一个字节数据
 * 参数	无
 * 返回	读取的字节数据，若读取失败则返回0
 * 说明	DATA引脚在高电平状态下被拉低54us，再拉高，读取拉高40us后的电平
 * 		j用来防止程序卡死在while等待中
 */
uint8_t DHT11_ReadByte(void)
{
    uint8_t i = 0, j = 0, Byte = 0;

    for (i = 0;i < 8;i++)
    {
        while (DHT11_DATA_IN()==GPIO_PIN_SET && j<100)
        {
        	j++;
        	Delay_us(1);
        }
        if(j >= 100)
        {
        	return 0;
        }
        j = 0;

        while (DHT11_DATA_IN()==GPIO_PIN_RESET && j<100)
        {
        	j++;
            Delay_us(1);
        }
        if(j >= 100)
        {
        	return 0;
        }
        j = 0;

        Delay_us(40);

        if (DHT11_DATA_IN() == GPIO_PIN_SET)
        {
        	Byte |= (uint8_t)(0x01 << (7 - i));
        }
        else
        {
        	Byte &= (uint8_t) ~(0x01 << (7 - i));
        }
    }
    return Byte;
}

/*
 * 函数	读取DHT11测得的温湿度值
 * 参数	无
 * 返回	读取成功返回DHT11_OK，读取失败返回DHT11_ERROR
 * 		温湿度信息写入对应结构体
 * 注意	主函数需要定义对应结构体
 */
uint8_t DHT11_Read(DHT11_Data_TypeDef *DHT11_Data)
{
	uint8_t i;			//防止卡死在while中的定时变量

	DHT11_Start();		//发送起始信号
	DHT11_Mode_IPU();	//改为输入模式

	//检测DHT11响应信号
	while(DHT11_DATA_IN() == GPIO_PIN_SET && i<100)
	{
		i++;
		Delay_us(1);
	}

	//超时表示DHT11未响应，直接返回DHT11_ERROR
	if(i >= 100)
		return DHT11_ERROR;
	i = 0;

	//检测DHT11响应信号
	while(DHT11_DATA_IN() == GPIO_PIN_RESET && i<100)
	{
		i++;
		Delay_us(1);
	}

	//超时表示DHT11未响应，直接返回DHT11_ERROR
	if(i >= 100)
		return DHT11_ERROR;
	i = 0;

	//读取温湿度数据
	DHT11_Data->humi_int = DHT11_ReadByte();
	DHT11_Data->humi_deci = DHT11_ReadByte();
	DHT11_Data->temp_int = DHT11_ReadByte();
	DHT11_Data->temp_deci = DHT11_ReadByte();
	DHT11_Data->check_sum = DHT11_ReadByte();

	//结束信号
	Delay_us(54);
	DHT11_Mode_Out_PP();
	DHT11_DATA_OUT(HIGH);

	//校验
	if (DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int + DHT11_Data->temp_deci)
		return DHT11_OK;
	else
		return DHT11_ERROR;

}
