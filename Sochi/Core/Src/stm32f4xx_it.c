/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Defines.h"
#include "Func.h"
#include "PidPos.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef Music
uint16_t frecs[128]={
	 Bm1, 0xFFFF, Bm1, 0xFFFF, Bm1, 0xFFFF, Bm1, 0xFFFF
	,Bm1, B1, Em2, Bm1, 0xFFFF, Bm1, 0xFFFF, Bm1, 0xFFFF
	,Bm1, B1, Em2, Bm1, 0xFFFF, Bm1, 0xFFFF
	,Bm1, B1, Em2, Bm1, 0xFFFF, Bm1, 0xFFFF
	
	,Bm1, B1, Em2, Bm1, 0xFFFF, Bm1, 0xFFFF
	,Bm1, B1, Em2, F2, 0xFFFF, F2, 0xFFFF
	,Am2, Fd2, F2, Em2,0xFFFF, Em2, 0xFFFF
	,Am2, Fd2, F2, Em2,0xFFFF, Em2, 0xFFFF
};

float tacts[128]={
	 0.1875, 0.0625, 0.1875, 0.0625, 0.1875, 0.0625, 0.1875, 0.0625
	,0.1875, 0.1875, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125, 0.125
	,0.1875, 0.1875, 0.125, 0.125, 0.125, 0.125, 0.125
	,0.1875, 0.1875, 0.125, 0.125, 0.125, 0.125, 0.125
	
	,0.1875, 0.1875, 0.125, 0.125, 0.125, 0.125, 0.125
	,0.1875, 0.1875, 0.125, 0.125, 0.125, 0.125, 0.125
	,0.1875, 0.1875, 0.125, 0.125, 0.125, 0.125, 0.125
	,0.1875, 0.1875, 0.125, 0.125, 0.125, 0.125, 0.125
};
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern uint8_t RxBuf[32];
extern uint8_t flag;
extern uint8_t CountIn;
extern int32_t CountR;
extern int32_t CountL;

extern float DistLeftM;
extern float DistRightM;
extern float SpeedLeftMS;
extern float SpeedRightMS;

extern uint32_t Servo5AngleRaw;
extern PID PID1;

#ifdef SettingMan
extern	uint32_t CountTest;
#endif

extern uint8_t CountSpace;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart6_tx;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	#ifdef Music
	static uint16_t count;
	static uint16_t next_time;
	static uint8_t pointer;
	static uint16_t countforbas;
	if(count>=next_time)
	{
		next_time=tact*tacts[pointer];
		TIM9->ARR=frecs[pointer];
	//	TIM9->CCR1=frecs[pointer]/3;
	//	TIM9->CCR2=frecs[pointer]/3;
		count=0;
		pointer ++;
		if(pointer>=64)
		{
			pointer=8;
		}
	}
	count++;
	#endif
	static uint32_t Count;
	static uint32_t CountServo5;
	
	
	if ((Count%50)==0)
	{
		flag|=(1<<TimeOk);
	}
	if((Count%20)==0)
	{
		flag|=(1<<StartCulcSpeed);
	}
	
	#ifdef PidVel
	if((Count%PidTimeMs)==0)
	{
		flag|=(1<<StartPidUpdate);
	}
	#endif
	
	#ifdef present
	if((Count%TimeSwitch)==0)
	{
		flag|=(1<<SwitchesColor);
	}
	
	#endif
	
	if((Count%500)==0)
	{
		HAL_GPIO_TogglePin(Led_GPIO_Port,Led_Pin);
	}
	Count++;
	
	if((flag&(1<<StartMovServo5))!=0)
	{
		if(CountServo5>=Servo5AngleRaw)
		{
			flag&=~(1<<StartMovServo5);
			flag|=(1<<FinishMovServo5);
			CountServo5=0;
		}
		else
		{
			CountServo5++;
		}
	}
	
	
	if(Count==(30000-1))
	{
		Count=0;
	}
	
	
	#ifdef SettingMan
		if((flag&(1<<StartSettingMan))!=0)
		{
			CountTest++;
		}
	#endif
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */
	HAL_GPIO_TogglePin(Trig_GPIO_Port,Trig_Pin);
	if((TIM10->SR&TIM_SR_UIF)!=0)
	{
		TIM3->CNT=0;
	}
  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  HAL_TIM_IRQHandler(&htim10);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles TIM1 trigger and commutation interrupts and TIM11 global interrupt.
  */
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 0 */
	HAL_GPIO_TogglePin(Servo5_GPIO_Port,Servo5_Pin);
	if((TIM11->SR&TIM_SR_UIF)!=0)
	{
		HAL_GPIO_WritePin(Servo5_GPIO_Port,Servo5_Pin,1);
	}
  /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  HAL_TIM_IRQHandler(&htim11);
  /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 1 */

  /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	static uint8_t CountUart6;
	static uint8_t CountSpaceUart;
	RxBuf[CountUart6]=(USART1->DR);//&(~(0x30));
	CountUart6++;
	
	if((RxBuf[CountUart6-1])==' ')
	{
		CountSpaceUart=CountSpaceUart+1;
	}
	
	if ((RxBuf[CountUart6-1]=='_')|(RxBuf[CountUart6-1]=='\r'))
	{
		CountIn=CountUart6;
		CountUart6=0;
		CountSpace=CountSpaceUart;
		CountSpaceUart=0;
		flag|=(1<<RecieveOk);
	}
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles TIM5 global interrupt.
  */
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */

  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&htim5);
  /* USER CODE BEGIN TIM5_IRQn 1 */

  /* USER CODE END TIM5_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream1 global interrupt.
  */
void DMA2_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream1_IRQn 0 */

  /* USER CODE END DMA2_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart6_rx);
  /* USER CODE BEGIN DMA2_Stream1_IRQn 1 */

  /* USER CODE END DMA2_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream6 global interrupt.
  */
void DMA2_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream6_IRQn 0 */

  /* USER CODE END DMA2_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart6_tx);
  /* USER CODE BEGIN DMA2_Stream6_IRQn 1 */

  /* USER CODE END DMA2_Stream6_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/**
  * @brief This function handles USART6 global interrupt.
  */
void USART6_IRQHandler(void)
{
  /* USER CODE BEGIN USART6_IRQn 0 */

  /* USER CODE END USART6_IRQn 0 */
  HAL_UART_IRQHandler(&huart6);
  /* USER CODE BEGIN USART6_IRQn 1 */

  /* USER CODE END USART6_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
