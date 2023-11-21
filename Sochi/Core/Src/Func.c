#include "Func.h"
#include "Defines.h"

extern uint8_t RxBuf[32];
extern uint8_t flag;
extern uint8_t CountIn;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

extern int32_t CountR;
extern int32_t CountL;

void StartState()
{
	TIM9->CCR1=MIN_PWM;
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	r_motor_stop();
	
	//encoder
	CountR=0;
	CountL=0;
	
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	TIM2->CCR1=0x7FFFFFFF;
	TIM2->CCR2=0x7FFFFFFE;
	
	//HC-sr04
	TIM10->CCR1=1;
	HAL_TIM_PWM_Start_IT(&htim10,TIM_CHANNEL_1);
	TIM10->DIER|=1;
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
	
	//Servo start pwm
	
	TIM11->CCR1=1500;
	HAL_TIM_PWM_Start_IT(&htim11,TIM_CHANNEL_1);
	TIM11->DIER|=1;
	
	TIM4->CCR1=1500;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	TIM4->CCR2=1500;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	TIM4->CCR3=1500;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	TIM4->CCR4=1500;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	
}

void r_motor_forv(uint16_t Velocity)
{
	TIM9->CCR1=Velocity;
	HAL_GPIO_WritePin(EN_R_A_GPIO_Port,EN_R_A_Pin,1);
	HAL_GPIO_WritePin(EN_R_B_GPIO_Port,EN_R_B_Pin,0);
}

void r_motor_back(uint16_t Velocity)
{
	TIM9->CCR1=Velocity;
	HAL_GPIO_WritePin(EN_R_A_GPIO_Port,EN_R_A_Pin,0);
	HAL_GPIO_WritePin(EN_R_B_GPIO_Port,EN_R_B_Pin,1);
}

void r_motor_stop()
{
//	TIM9->CCR1=Velocity;
	HAL_GPIO_WritePin(EN_R_A_GPIO_Port,EN_R_A_Pin,1);
	HAL_GPIO_WritePin(EN_R_B_GPIO_Port,EN_R_B_Pin,1);
}

void ServoWrite1(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM4->CCR1=350+pos/120;
}

void ServoWrite2(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM4->CCR2=350+pos/120;
}

void ServoWrite3(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM4->CCR3=350+pos/120;
}

void ServoWrite4(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM4->CCR4=350+pos/120;
}

void ServoWrite5(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM11->CCR1=350+pos/120;
}

void Update()
{
	int32_t data=0;
	if (RxBuf[2]=='-')
	{
		for (uint8_t i=3;i<CountIn-1;i++)
		{
			data=data*10+(RxBuf[i]&(~0x30));
		}
		data=data*(-1);
	}
	else
	{
		for (uint8_t i=2;i<CountIn-1;i++)
		{
			data=data*10+(RxBuf[i]&(~0x30));
		}
	}
	switch (RxBuf[0])
	{
		case 'P':
			switch (RxBuf[1])
			{
				case 'R':
					if (data>=0)
					{
						r_motor_forv(data);
					}
					else
					{
						if(data==0)
						{
							r_motor_stop();
						}
						r_motor_back(abs(data));
					}
			}
			break;
		case 'A':
			switch (RxBuf[1])
			{
				case '1':
						ServoWrite1((uint16_t)data);
				break;
				case '2':
						ServoWrite2((uint16_t)data);
				break;
				case '3':
						ServoWrite3((uint16_t)data);
				break;
				case '4':
						ServoWrite4((uint16_t)data);
				break;
				case '5':
						ServoWrite5((uint16_t)data);
				break;
			}
			break;
		case 'S':
			switch (RxBuf[1])
			{
				case '1':
						TIM4->CCR1=data;
				break;
				case '2':
						TIM4->CCR2=data;
				break;
				case '3':
						TIM4->CCR3=data;
				break;
				
				case '4':
						TIM4->CCR4=data;
				break;
				case '5':
						TIM11->CCR1=data;
				break;
			}
			break;
			
	}
	
}