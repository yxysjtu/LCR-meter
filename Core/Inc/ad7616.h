//***************************************************************************************
//
// 程    序: ADS8688驱动代码
// 作　　者: 科一电子
// 日    期: 2020-11-11
// 实验平台: 科一电子  STM32F103核心板
// 说　　明:
// 购买地址:qzkydz.taobao.com
//
//***************************************************************************************
#ifndef _ADS8688_H_
#define _ADS8688_H_
#ifdef __cplusplus
extern "C" {
#endif
//***************************************************************************************
// 头文件包含
//***************************************************************************************
//#include "./systemclk.h"
#include "main.h"

/* AD7616输入电压范围 */
#define ad7616_range    	10000.0	/* AD7616量程 */

#define Range_10V      	0x0000
#define Range_5V      	0x00AA
#define Range_2V5      	0x0055

//***************************************************************************************
// 引脚声明
//***************************************************************************************
#define AD7616_RESET_L      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET)
#define AD7616_RESET_H     	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET)
//#define AD7616_SEQEN_L      HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_RESET)
//#define AD7616_SEQEN_H     	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET)
//#define AD7616_RNGSEL1_L    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET)
//#define AD7616_RNGSEL1_H    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET)
//#define AD7616_RNGSEL0_L    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET)
//#define AD7616_RNGSEL0_H    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET)
#define AD7616_SER_L    	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_RESET)
#define AD7616_SER_H    	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_SET)

//#define AD7616_D0_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET)
//#define AD7616_D0_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET)
//#define AD7616_D1_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET)
//#define AD7616_D1_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET)
//#define AD7616_D2_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET)
//#define AD7616_D2_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET)
//#define AD7616_D3_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET)
//#define AD7616_D3_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET)
#define AD7616_D4_SER1W_L   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET)//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET)
#define AD7616_D4_SER1W_H   HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET)//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_SET)
//#define AD7616_D5_CRCEN_L   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET)
//#define AD7616_D5_CRCEN_H   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET)
//#define AD7616_D6_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET)
//#define AD7616_D6_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET)
//#define AD7616_D7_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET)
//#define AD7616_D7_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET)
//#define AD7616_D8_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_RESET)
//#define AD7616_D8_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_SET)
//#define AD7616_D9_L    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_RESET)
//#define AD7616_D9_H    		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_SET)
#define AD7616_D10_SDI_L    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET)//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET)
#define AD7616_D10_SDI_H    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET)//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET)

#define AD7616_D11_SDOB    	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)//HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11)
#define AD7616_D12_SDOA    	HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)//HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_12)

//#define AD7616_D13_OS0_L    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET)
//#define AD7616_D13_OS0_H    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET)
//#define AD7616_D14_OS1_L    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET)
//#define AD7616_D14_OS1_H    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET)
//#define AD7616_D15_OS2_L    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET)
//#define AD7616_D15_OS2_H    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_SET)

//#define AD7616_WR_L    		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET)
//#define AD7616_WR_H    		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET)
#define AD7616_SCLK_L    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET)
#define AD7616_SCLK_H    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET)
#define AD7616_CS_L    		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET)
#define AD7616_CS_H    		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET)//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET)
//#define AD7616_CHSEL0_L    	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_RESET)
//#define AD7616_CHSEL0_H    	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET)
//#define AD7616_CHSEL1_L    	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET)
//#define AD7616_CHSEL1_H    	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET)
//#define AD7616_CHSEL2_L    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)
//#define AD7616_CHSEL2_H    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)

#define AD7616_BUSY    		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)//HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)

#define AD7616_CONVST_L    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET)//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET)
#define AD7616_CONVST_H    	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET)//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET)

//***************************************************************************************
// 外部函数声明
//***************************************************************************************
extern void AD7616_Init(void);
extern void AD7616_Reset(void);
extern void AD7616_Start_Convst(void);
extern void AD7616_Read_Data(int16_t * cha_data, int16_t * chb_data);
extern void AD7616_Write_Data(uint16_t txdata);

extern void Delay_ms(uint32_t delay_ms);
extern void Delay_us(uint32_t delay_us);

#ifdef __cplusplus
}
#endif
#endif
