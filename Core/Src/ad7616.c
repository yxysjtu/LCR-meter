//***************************************************************************************
//
// 程    序: AD7616驱动代码
// 作　　者: 科一电子
// 日    期: 2020-11-11
// 实验平台: 科一电子  STM32F103核心板
// 说　　明:
// 购买地址:qzkydz.taobao.com
//
//***************************************************************************************
#include "ad7616.h"
//#include "./delay.h"

void Delay_ms(uint32_t delay_ms){
	HAL_Delay(delay_ms - 1);
}

void Delay_us(uint32_t delay_us){
	for(int i = 0; i < delay_us * 150 ; i++){
		;
	}
}


//***************************************************************************************
// 
// 函数功能: AD7616初始化
// 入口参数: 无
// 返 回 值: 无
// 说    明: 无
//
//***************************************************************************************
void AD7616_Init(void)
{
	GPIO_InitTypeDef gpio_init_struct;
	__HAL_RCC_GPIOB_CLK_ENABLE();					  	/* 开启GPIOF时钟使能 */
	__HAL_RCC_GPIOC_CLK_ENABLE();					  	/* 开启GPIOF时钟使能 */
	__HAL_RCC_GPIOF_CLK_ENABLE();					  	/* 开启GPIOF时钟使能 */
	__HAL_RCC_GPIOG_CLK_ENABLE();					  	/* 开启GPIOG时钟使能 */
	
	gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
						   GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
						   GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
						   GPIO_PIN_13| GPIO_PIN_14| GPIO_PIN_15;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;      	/* 推挽输出 */
	gpio_init_struct.Pull = GPIO_PULLUP;              	/* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;    	/* 高速 */
	HAL_GPIO_Init(GPIOG, &gpio_init_struct);       	  	/* 初始化引脚 */
	
	gpio_init_struct.Pin = GPIO_PIN_11|GPIO_PIN_12;
	gpio_init_struct.Mode = GPIO_MODE_INPUT;      		/* 推挽输出 */
	gpio_init_struct.Pull = GPIO_PULLUP;              	/* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;    	/* 高速 */
	HAL_GPIO_Init(GPIOG, &gpio_init_struct);       	  	/* 初始化引脚 */
	
	gpio_init_struct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |GPIO_PIN_4 | 
						   GPIO_PIN_5 | GPIO_PIN_11| GPIO_PIN_12| 
						   GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;      	/* 推挽输出 */
	gpio_init_struct.Pull = GPIO_PULLUP;              	/* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;    	/* 高速 */
	HAL_GPIO_Init(GPIOF, &gpio_init_struct);       	  	/* 初始化引脚 */
	
	gpio_init_struct.Pin = GPIO_PIN_1;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;      	/* 推挽输出 */
	gpio_init_struct.Pull = GPIO_PULLUP;              	/* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;    	/* 高速 */
	HAL_GPIO_Init(GPIOB, &gpio_init_struct);       	  	/* 初始化引脚 */
	
	gpio_init_struct.Pin = GPIO_PIN_0;
	gpio_init_struct.Mode = GPIO_MODE_INPUT;      	/* 推挽输出 */
	gpio_init_struct.Pull = GPIO_NOPULL;              	/* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;    	/* 高速 */
	HAL_GPIO_Init(GPIOB, &gpio_init_struct);       	  	/* 初始化引脚 */
	
	gpio_init_struct.Pin = GPIO_PIN_5;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;      	/* 推挽输出 */
	gpio_init_struct.Pull = GPIO_PULLUP;              	/* 上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;    	/* 高速 */
	HAL_GPIO_Init(GPIOC, &gpio_init_struct);       	  	/* 初始化引脚 */
	
//	AD7616_SEQEN_L;			// 软件模式
//	AD7616_RNGSEL0_L;
//	AD7616_RNGSEL1_L;		// 输入范围通过软件配置
	AD7616_SER_H;			// 串行接口
//	AD7616_D0_L;			// 串行模式必须拉低
//	AD7616_D1_L;			// 串行模式必须拉低
//	AD7616_D2_L;			// 串行模式必须拉低
//	AD7616_D3_L;			// 串行模式必须拉低
	AD7616_D4_SER1W_H;		// 数据输出口位SDOA和SDOB
//	AD7616_D5_CRCEN_L;		// 无校验字
//	AD7616_D6_L;			// 串行模式必须拉低
//	AD7616_D7_L;			// 串行模式必须拉低
//	AD7616_D8_L;			// 串行模式必须拉低
//	AD7616_D9_L;			// 串行模式必须拉低
//	AD7616_D13_OS0_L;		// 软件串行模式必须拉低
//	AD7616_D14_OS1_L;		// 软件串行模式必须拉低
//	AD7616_D15_OS2_L;		// 软件串行模式必须拉低
//	AD7616_WR_L;			// 软件串行模式必须拉低
	AD7616_SCLK_H;			// 串行时钟拉低
	AD7616_CS_H;			// 片选拉高
//	AD7616_CHSEL0_L;		// 软件模式下必须拉低
//	AD7616_CHSEL1_L;		// 软件模式下必须拉低
//	AD7616_CHSEL2_L;		// 软件模式下必须拉低
	AD7616_CONVST_L;
	
	Delay_ms(1);
	AD7616_Reset();
	Delay_ms(10);
	
	AD7616_Write_Data(0x8400);				// 配置寄存器
	AD7616_Write_Data(0x8600);				// 通道寄存器，
	AD7616_Write_Data(0x8800|Range_10V);	// ±10V输入范围
	AD7616_Write_Data(0x8A00|Range_10V);	// ±10V输入范围
	AD7616_Write_Data(0x8C00|Range_10V);	// ±10V输入范围
	AD7616_Write_Data(0x8E00|Range_10V);	// ±10V输入范围
}

//***************************************************************************************
// 
// 函数功能: AD7616硬件复位
// 入口参数: 无
// 返 回 值: 无
// 说    明: 无
//
//***************************************************************************************
void AD7616_Reset(void)
{ 
	AD7616_RESET_H;
	Delay_us (1);
	AD7616_RESET_L; 
	Delay_us(1);
	AD7616_RESET_H; 
} 

//***************************************************************************************
// 
// 函数功能: AD7616启动转换
// 入口参数: 无
// 返 回 值: 无
// 说    明: 无
//
//***************************************************************************************
void AD7616_Start_Convst(void)
{  
	AD7616_CONVST_H;
	AD7616_CONVST_H;
	Delay_us (1);
	AD7616_CONVST_L;
	AD7616_CONVST_L;
	Delay_us (1);
}

//***************************************************************************************
// 
// 函数功能: AD7616读取通道A和通道B的采集数据
// 入口参数: 获取通道A和通道B的采集数据
// 返 回 值: 无
// 说    明: 无
//
//***************************************************************************************
void AD7616_Read_Data(int16_t * cha_data, int16_t * chb_data)
{
	uint8_t i;
    uint16_t rxdata_a = 0;
	uint16_t rxdata_b = 0;
	AD7616_CS_L;
    for(i=0; i<16; i++)
	{		
		rxdata_a = rxdata_a<<1;
		rxdata_b = rxdata_b<<1;
		AD7616_SCLK_L;
		if (AD7616_D12_SDOA  == GPIO_PIN_SET)
			rxdata_a++;	
		if (AD7616_D11_SDOB  == GPIO_PIN_SET)
			rxdata_b++;	
		AD7616_SCLK_H;
	}
	AD7616_CS_H;
	*cha_data = rxdata_a;
	*chb_data = rxdata_b;
}

//***************************************************************************************
// 
// 函数功能: AD7616写一个16位数据
// 入口参数: txdata：写入的数据
// 返 回 值: 无
// 说    明: 无
//
//***************************************************************************************
void AD7616_Write_Data(uint16_t txdata)
{
	uint8_t i;
	
	AD7616_CS_L;
    for(i=0; i<16; i++)
	{	
		if(txdata & 0x8000)
		{
			AD7616_D10_SDI_H;
		}
		else
		{
			AD7616_D10_SDI_L;
		}		
		AD7616_SCLK_L;
		txdata <<= 1;
		AD7616_SCLK_H;
		
	}
	AD7616_CS_H;
	AD7616_D10_SDI_L;
}
