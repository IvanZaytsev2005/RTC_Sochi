#include "Encoder.h"
#include "Func.h"
#include "Defines.h"

extern int32_t CountR;
extern int32_t CountL;

extern uint32_t Time1;
extern uint32_t Time2;
extern float length1;
extern float length2;

extern uint16_t SmaBufT1[SmaN];
extern uint16_t SmaBufT2[SmaN];
extern uint8_t CountPosL1;
extern uint8_t CountPosL2;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	static uint32_t CCR1_Start;
	static uint32_t CCR3_Start;
	if(htim->Instance==TIM2)
	{
		uint32_t currCounter = TIM2->CNT;
		if (currCounter>0x80000000)
		{
			CountR=currCounter-0xFFFFFFFF;
		}
		else
		{
			CountR =currCounter;
		}
	}
	 if(htim->Instance == TIM3)
		{
			if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) // RISING ? LOW ?? HIGH
			{
				//__HAL_TIM_SET_COUNTER(htim, 0x0000); // ????????? ????????
				CCR3_Start=TIM3->CCR3;
      }
      else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) // FALLING ? HIGH ?? LOW
			{
				uint16_t Temp=TIM3->CCR4-CCR3_Start;
				Time2 = SMA(SmaBufT2,Temp,&CountPosL2); // 
				length2=(float)(Time2/58);
      }
			
			if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // RISING ? LOW ?? HIGH
			{
				//__HAL_TIM_SET_COUNTER(htim, 0x0000); // ????????? ????????
				CCR1_Start=TIM3->CCR1;
      }
      else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) // FALLING ? HIGH ?? LOW
			{
				Time1 = TIM3->CCR2-CCR1_Start; // 
				length1=(float)Time1/58;
      }
    }
	
}