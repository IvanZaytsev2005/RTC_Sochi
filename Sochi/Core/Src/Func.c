#include "Func.h"
#include "Defines.h"
#include "PidVel.h"

extern uint8_t RxBuf[32];
extern uint8_t flag;
extern uint8_t CountIn;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

extern UART_HandleTypeDef huart1;

extern int32_t CountR;
extern int32_t CountL;

extern uint8_t TxBuf[50];

extern int32_t SpeedTickR;
extern int32_t SpeedTickL;

extern float DistLeftM;
extern float DistRightM;
extern float SpeedLeftMS;
extern float SpeedRightMS;

extern float SpeedLeftMS;
extern float SpeedRightMS;

extern float TargetSpeedLeftMS;
extern float TargetSpeedRightMS;

extern float Kp;
extern float Kd;
extern float Ki;
extern uint16_t Ko;

#ifdef PidVelArduino

extern uint8_t moving;
extern SetPointInfo leftPID, rightPID;
#endif

int32_t LastCountR;
int32_t LastCountL;

extern uint8_t CountSpace;

extern uint16_t ServoDeg[5];

extern uint32_t Servo5AngleRaw;

#ifdef SettingMan
extern	uint32_t CountTest;
#endif

void StartState()
{
	l_motor_stop();
	r_motor_stop();
	TIM9->CCR1=MIN_PWM;
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	TIM9->CCR2=MIN_PWM;
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	
	
	//encoder
	CountR=0;
	CountL=0;
	
	HAL_TIM_Encoder_Start_IT(&htim2,TIM_CHANNEL_ALL);
	TIM2->CCR1=0x7FFFFFFF;
	TIM2->CCR2=0x7FFFFFFE;
	
	HAL_TIM_Encoder_Start_IT(&htim5,TIM_CHANNEL_ALL);
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
	TIM4->CCR4=0;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	
	ServoWrite1(ZeroStateServo1);
	ServoWrite2(ZeroStateServo2);
	ServoWrite3(ZeroStateServo3);
	ServoWrite4(ZeroStateServo4);
//	ServoWrite5(ZeroStateServo5);
	
	ServoDeg[0]=ZeroStateServo1;
	ServoDeg[1]=ZeroStateServo2;
	ServoDeg[2]=ZeroStateServo3;
	ServoDeg[3]=ZeroStateServo4;
	ServoDeg[4]=ZeroStateServo5;
	#ifdef PidVel
	Kp = 1200;
	Kd = 500;
	Ki = 300;
	
	TargetSpeedRightMS=0.05;
	TargetSpeedRightMS=0;
	#endif
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

void l_motor_forv(uint16_t Velocity)
{
	TIM9->CCR2=Velocity;
	HAL_GPIO_WritePin(EN_L_A_GPIO_Port,EN_L_A_Pin,1);
	HAL_GPIO_WritePin(EN_L_B_GPIO_Port,EN_L_B_Pin,0);
}

void l_motor_back(uint16_t Velocity)
{
	TIM9->CCR2=Velocity;
	HAL_GPIO_WritePin(EN_L_A_GPIO_Port,EN_L_A_Pin,0);
	HAL_GPIO_WritePin(EN_L_B_GPIO_Port,EN_L_B_Pin,1);
}

void l_motor_stop()
{
//	TIM9->CCR1=Velocity;
	HAL_GPIO_WritePin(EN_L_A_GPIO_Port,EN_L_A_Pin,1);
	HAL_GPIO_WritePin(EN_L_B_GPIO_Port,EN_L_B_Pin,1);
}

void ServoWrite5(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM4->CCR4=350+pos/180;
	
}

void ServoWrite2(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM4->CCR1=350+pos/180;
}

void ServoWrite3(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM4->CCR2=350+pos/180;
}

void ServoWrite1(uint16_t Angle)
{
	uint32_t pos=Angle*2150;
	TIM11->CCR1=350+pos/180;
}

void ServoWrite4(uint16_t Angle)
{	
	uint32_t pos=Angle*2150;
	TIM4->CCR3=350+pos/180;
	
}

void Update()
{
//////	int32_t data=0;
//////	if (RxBuf[2]=='-')
//////	{
//////		for (uint8_t i=3;i<CountIn-1;i++)
//////		{
//////			data=data*10+(RxBuf[i]&(~0x30));
//////		}
//////		data=data*(-1);
//////	}
//////	else
//////	{
//////		for (uint8_t i=2;i<CountIn-1;i++)
//////		{
//////			data=data*10+(RxBuf[i]&(~0x30));
//////		}
//////	}
	
	int32_t datal=0;
	int32_t datar=0;
	
	if(CountSpace==1)
	{
		if (RxBuf[2]=='-')
		{
			for (uint8_t i=3;i<CountIn-1;i++)
			{
				datal=datal*10+(RxBuf[i]&(~0x30));
			}
			datal=datal*(-1);
		}
		else
		{
			for (uint8_t i=2;i<CountIn-1;i++)
			{
				datal=datal*10+(RxBuf[i]&(~0x30));
			}
		}
	}
	if (CountSpace==2)
	{
		uint8_t i;
		if (RxBuf[2]=='-')
		{
			i=3;
			while(RxBuf[i]!=' ')
			{
				datal=datal*10+(RxBuf[i]&(~0x30));
				i++;
			}
			datal=datal*(-1);
		}
		else
		{
			i=2;
			while(RxBuf[i]!=' ')
			{
				datal=datal*10+(RxBuf[i]&(~0x30));
				i++;
			}
		}
		
		if(RxBuf[i+1]=='-')
		{
			i=i+2;
			while(RxBuf[i]!='_')
			{
				datar=datar*10+(RxBuf[i]&(~0x30));
				i++;
			}
			datar=datar*(-1);
		}
		else
		{
			i=i+1;
			while(RxBuf[i]!='_')
			{
				datar=datar*10+(RxBuf[i]&(~0x30));
				i++;
			}
		}
		
	}
	
	
	uint16_t S;
	
	switch(RxBuf[0])
	{
		case 'O':
			setMotorSpeeds(datar, datal);
			TransmitOK();
		break;
		case 'E'://get encoders
			S=OutEnc(CountL, CountR, TxBuf);
			HAL_UART_Transmit_DMA(&huart1,TxBuf,S);
		break;
		case 'D':
			S=OutDistance(DistLeftM,DistRightM,TxBuf);
			HAL_UART_Transmit_DMA(&huart1,TxBuf,S);
		break;
		case 'V':
			S=OutDistance(SpeedLeftMS,SpeedRightMS,TxBuf);
			HAL_UART_Transmit_DMA(&huart1,TxBuf,S);
		break;
		case 'R':// reset encoders
			TIM2->CNT=0;
			TIM5->CNT=0;
			CountR=0;
			CountL=0;
			TransmitOK();
		break;
		#ifdef PidVel
		case 'M':
			TargetSpeedLeftMS = (float)datal/1000;
			TargetSpeedRightMS = (float)datar/1000;
			TransmitOK();
		break;
		case 'L':
			TargetSpeedLeftMS = 0.1;
			TargetSpeedRightMS = 0.1;
			Servo5AngleRaw=datal;
			flag|=(1<<StartMovServo5);
			TransmitOK();
		break;
		#endif
		case 'p':
			Kp=datal;
			TransmitOK();
		break;
		case 'i':
			Ki=datal;
			TransmitOK();
		break;
		case 'd':
			Kd=datal;
			TransmitOK();
		break;
		case 'S':
			switch(datal)
			{
				case 1:
					ServoWrite1(datar);
				break;
				case 2:
					ServoWrite2(datar);
				break;
				case 3:
					ServoWrite3(datar);
				break;
				case 4:
					ServoWrite4(datar);
				break;
				case 5:
					//ServoWrite5(datar);
					if(datar>0)
					{
						Servo5AngleRaw=datar*200/9;
						flag|=(1<<StartMovServo5);
						TIM4->CCR4=SpeedServo5Right;
					}
					else
					{
						Servo5AngleRaw=(uint32_t)((-1)*datar)*200/9;
						flag|=(1<<StartMovServo5);
						TIM4->CCR4=SpeedServo5Left;
					}
					
				break;
			}				
			ServoDeg[datal-1]=(uint16_t)(datar);
			TransmitOK();
		break;
		case 'T':
			S=sprintf(TxBuf,"%d",ServoDeg[((uint32_t)(datal-1))]);
		TxBuf[S]='\r';
			HAL_UART_Transmit_DMA(&huart1,TxBuf,S+1);
		break;
		#ifdef SettingMan
		case 'J':
			switch(datal)
			{
				case 0:
					S=sprintf(TxBuf,"%d",CountTest);
					flag&=~(1<<StartSettingMan);
				case 1:
					flag|=(1<<StartMovServo5);
					Servo5AngleRaw=Servo5TestAngleRaw;
					TIM4->CCR4=datar;
					TransmitOK();
				break;
				case 2:
					flag|=(1<<StartMovServo5);
					Servo5AngleRaw=Servo5TestAngleRaw;
					TIM4->CCR4=datar;
					TransmitOK();
				break;
			}
			
		break;
		
		#endif
				
	}
	

	
}

uint16_t SMA(uint16_t *data, uint16_t New, uint8_t *CountPos)
{
//	static uint8_t CountPos;
	int32_t Sum=0;
	//uint32_t a=data;
	data=data+(*CountPos%SmaN);
	*data=New;
	data=data-(*CountPos%SmaN);
	if(*CountPos==0)
	{
		*CountPos=*CountPos+1;
		return(New);
	}
	if(*CountPos>=SmaN)
	{
		for(char i=0; i<SmaN; i++)
		{
			Sum=Sum+*data/SmaN;
			data++;
		}
		*CountPos=*CountPos+1;
		if(*CountPos>=(2*SmaN))
		{
			*CountPos=SmaN;
		}
		return((int16_t)Sum);
	}
	else
	{
		for(char i=0;i<*CountPos;i++)
		{
			Sum=Sum+*data;
			data++;
		}
		*CountPos=*CountPos+1;
		return((int16_t)Sum/(*CountPos-1));
	}
}

uint16_t OutPlot(float data1, float data2, uint8_t *Buf)
{
	*Buf='$';
	Buf++;
	uint8_t S=sprintf(Buf,"%f",data1);
	Buf=Buf+S;
	*Buf=' ';
	Buf++;
	uint8_t D=sprintf(Buf,"%f",data2);
	Buf=Buf+D;
/*	*Buf=' ';
	Buf++;
	uint8_t F=sprintf(Buf,"%d",data3);
	Buf=Buf+F;*/
	*Buf=';';
	return(4+S+D);//+F);
}

uint16_t OutEnc(int32_t data1, int32_t data2, uint8_t *Buf)
{
	uint8_t S=sprintf(Buf,"%d",data1);
	Buf=Buf+S;
	*Buf=' ';
	Buf++;
	uint8_t D=sprintf(Buf,"%d",data2);
	Buf=Buf+D;
	*Buf='\r';
	return(2+S+D);
}

uint16_t OutDistance(float data1, float data2, uint8_t *Buf)
{
	uint8_t S=sprintf(Buf,"%f",data1);
	Buf=Buf+S;
	*Buf=' ';
	Buf++;
	uint8_t D=sprintf(Buf,"%f",data2);
	Buf=Buf+D;
	*Buf='\r';
	return(2+S+D);
}

void SpeedCulcTick()
{
	static float DistLeftMLast;
	static float DistRightMLast;
	SpeedLeftMS=(DistLeftM-DistLeftMLast)*50;
	SpeedRightMS=(DistRightM-DistRightMLast)*50;
	DistLeftMLast=DistLeftM;
	DistRightMLast=DistRightM;
	
}

void TransmitOK()
{
	TxBuf[0]='Z';
	TxBuf[1]='A';
	TxBuf[2]='E';
	TxBuf[3]='B';
	TxBuf[4]='I';
	TxBuf[5]='C';
	
	TxBuf[6]='\r';
	HAL_UART_Transmit_DMA(&huart1,TxBuf,7);
}

void setMotorSpeeds(int16_t VelL, int16_t VelR)
{
	if((abs(VelL)>MinMotorPWM)|(abs(VelR)>MinMotorPWM))
	{
		if(VelL>0)
		{
			l_motor_forv(VelL);
		}
		else
		{
			if(VelL==0)
			{
				l_motor_stop();
			}
			else
			{
				l_motor_back((uint16_t)((-1)*VelL));
			}
		}
		
		if(VelR>0)
		{
			r_motor_forv(VelR);
		}
		else
		{
			if(VelR==0)
			{
				r_motor_stop();
			}
			else
			{
				r_motor_back((uint16_t)((-1)*VelR));
			}
		}
	}
}