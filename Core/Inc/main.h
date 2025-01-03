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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define ENC1_CHA_Pin GPIO_PIN_0
#define ENC1_CHA_GPIO_Port GPIOA
#define ENC1_CHB_Pin GPIO_PIN_1
#define ENC1_CHB_GPIO_Port GPIOA
#define INT_3_Pin GPIO_PIN_5
#define INT_3_GPIO_Port GPIOA
#define ENC2_A_Pin GPIO_PIN_6
#define ENC2_A_GPIO_Port GPIOA
#define ENC2_B_Pin GPIO_PIN_7
#define ENC2_B_GPIO_Port GPIOA
#define I2C_SCL_Pin GPIO_PIN_10
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_11
#define I2C_SDA_GPIO_Port GPIOB
#define PWM_MOTOR2_Pin GPIO_PIN_8
#define PWM_MOTOR2_GPIO_Port GPIOA
#define PWM_MOTOR1_Pin GPIO_PIN_9
#define PWM_MOTOR1_GPIO_Port GPIOA
#define FOR_MOTOR1_Pin GPIO_PIN_15
#define FOR_MOTOR1_GPIO_Port GPIOA
#define REV_MOTOR1_Pin GPIO_PIN_3
#define REV_MOTOR1_GPIO_Port GPIOB
#define FOR_MOTOR2_Pin GPIO_PIN_4
#define FOR_MOTOR2_GPIO_Port GPIOB
#define REV_MOTOR2_Pin GPIO_PIN_5
#define REV_MOTOR2_GPIO_Port GPIOB
#define UART1_TX_Pin GPIO_PIN_6
#define UART1_TX_GPIO_Port GPIOB
#define UART1_RX_Pin GPIO_PIN_7
#define UART1_RX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
