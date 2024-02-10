/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Led_Pin GPIO_PIN_13
#define Led_GPIO_Port GPIOC
#define EN_R_A_Pin GPIO_PIN_14
#define EN_R_A_GPIO_Port GPIOC
#define EN_R_B_Pin GPIO_PIN_15
#define EN_R_B_GPIO_Port GPIOC
#define Enc_L_A_Pin GPIO_PIN_0
#define Enc_L_A_GPIO_Port GPIOA
#define Enc_L_B_Pin GPIO_PIN_1
#define Enc_L_B_GPIO_Port GPIOA
#define Motor1_PWM_Pin GPIO_PIN_2
#define Motor1_PWM_GPIO_Port GPIOA
#define Motor2_PWM_Pin GPIO_PIN_3
#define Motor2_PWM_GPIO_Port GPIOA
#define Enc_R_A_Pin GPIO_PIN_5
#define Enc_R_A_GPIO_Port GPIOA
#define Trig_Pin GPIO_PIN_7
#define Trig_GPIO_Port GPIOA
#define EN_L_A_Pin GPIO_PIN_12
#define EN_L_A_GPIO_Port GPIOB
#define EN_L_B_Pin GPIO_PIN_13
#define EN_L_B_GPIO_Port GPIOB
#define Enc_R_B_Pin GPIO_PIN_3
#define Enc_R_B_GPIO_Port GPIOB
#define Servo5_Pin GPIO_PIN_4
#define Servo5_GPIO_Port GPIOB
#define Servo1_Pin GPIO_PIN_6
#define Servo1_GPIO_Port GPIOB
#define Servo2_Pin GPIO_PIN_7
#define Servo2_GPIO_Port GPIOB
#define Servo4_Pin GPIO_PIN_8
#define Servo4_GPIO_Port GPIOB
#define Servo3_Pin GPIO_PIN_9
#define Servo3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
