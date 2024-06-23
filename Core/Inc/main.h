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
#include "stm32f4xx_hal.h"

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
#define LED_PIN_Pin GPIO_PIN_13
#define LED_PIN_GPIO_Port GPIOC
#define DT_ROTARY_Pin GPIO_PIN_1
#define DT_ROTARY_GPIO_Port GPIOA
#define DT_ROTARY_EXTI_IRQn EXTI1_IRQn
#define CLK_ROTARY_Pin GPIO_PIN_2
#define CLK_ROTARY_GPIO_Port GPIOA
#define CLK_ROTARY_EXTI_IRQn EXTI2_IRQn
#define LED_GREEN_Pin GPIO_PIN_3
#define LED_GREEN_GPIO_Port GPIOA
#define LED_YELLOW_Pin GPIO_PIN_4
#define LED_YELLOW_GPIO_Port GPIOA
#define LCD_RES_Pin GPIO_PIN_0
#define LCD_RES_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_2
#define BUZZER_GPIO_Port GPIOB
#define ERROR_LED_Pin GPIO_PIN_10
#define ERROR_LED_GPIO_Port GPIOB
#define B6_SCL_Pin GPIO_PIN_6
#define B6_SCL_GPIO_Port GPIOB
#define B7_SDA_Pin GPIO_PIN_7
#define B7_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
