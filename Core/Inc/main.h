/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define SERACC_HUART huart5
#define SERACC_HDMA hdma_uart5_rx
#include "seracc.h"
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
#define UI_SEG2_Pin GPIO_PIN_2
#define UI_SEG2_GPIO_Port GPIOE
#define UI_SEG3_Pin GPIO_PIN_3
#define UI_SEG3_GPIO_Port GPIOE
#define UI_SEG4_Pin GPIO_PIN_4
#define UI_SEG4_GPIO_Port GPIOE
#define UI_SW3_Pin GPIO_PIN_13
#define UI_SW3_GPIO_Port GPIOC
#define LCD_DC_Pin GPIO_PIN_9
#define LCD_DC_GPIO_Port GPIOF
#define LCD_RES_Pin GPIO_PIN_2
#define LCD_RES_GPIO_Port GPIOF
#define UI_LED0_Pin GPIO_PIN_11
#define UI_LED0_GPIO_Port GPIOD
#define Relay_SET_Pin GPIO_PIN_6
#define Relay_SET_GPIO_Port GPIOC
#define Relay_RST_Pin GPIO_PIN_7
#define Relay_RST_GPIO_Port GPIOC
#define UI_LED1_Pin GPIO_PIN_9
#define UI_LED1_GPIO_Port GPIOA
#define UI_LED2_Pin GPIO_PIN_10
#define UI_LED2_GPIO_Port GPIOA
#define UI_KC0_Pin GPIO_PIN_3
#define UI_KC0_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOD
#define UI_KC1_Pin GPIO_PIN_6
#define UI_KC1_GPIO_Port GPIOD
#define UI_LED3_Pin GPIO_PIN_8
#define UI_LED3_GPIO_Port GPIOB
#define UI_KC2_Pin GPIO_PIN_9
#define UI_KC2_GPIO_Port GPIOB
#define UI_SEG0_Pin GPIO_PIN_0
#define UI_SEG0_GPIO_Port GPIOE
#define UI_SEG1_Pin GPIO_PIN_1
#define UI_SEG1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
