#include "PidVel.h"
#include "Func.h"
#include "Defines.h"

extern float Kp;
extern float Kd;
extern float Ki;
//extern uint16_t Ko;

#ifdef PidVelArduino


extern uint8_t moving;


extern int32_t CountR;
extern int32_t CountL;

extern SetPointInfo leftPID, rightPID;

void resetPID()
{
   leftPID.TargetTicksPerFrame = 0.0;
   leftPID.Encoder = CountL;
   leftPID.PrevEnc = leftPID.Encoder;
   leftPID.output = 0;
   leftPID.PrevInput = 0;
   leftPID.ITerm = 0;

   rightPID.TargetTicksPerFrame = 0.0;
   rightPID.Encoder = CountR;
   rightPID.PrevEnc = rightPID.Encoder;
   rightPID.output = 0;
   rightPID.PrevInput = 0;
   rightPID.ITerm = 0;
}
	
/* PID routine to compute the next motor commands */
void doPID(SetPointInfo *p)
{
  int32_t Perror;
  int32_t output;
	int32_t input;

  //Perror = p->TargetTicksPerFrame - (p->Encoder - p->PrevEnc);
  input = p->Encoder - p->PrevEnc;
  Perror = p->TargetTicksPerFrame - input;


  /*
  * Avoid derivative kick and allow tuning changes,
  * see http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-derivative-kick/
  * see http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-tuning-changes/
  */
  //output = (Kp * Perror + Kd * (Perror - p->PrevErr) + Ki * p->Ierror) / Ko;
  // p->PrevErr = Perror;
  output = (Kp * Perror - Kd * (input - p->PrevInput) + p->ITerm) / Ko;
  p->PrevEnc = p->Encoder;

  output += p->output;
  // Accumulate Integral error *or* Limit output.
  // Stop accumulating when output saturates
  if (output >= MAX_PWM)
    output = MAX_PWM;
  else if (output <= -MAX_PWM)
    output = -MAX_PWM;
  else
  /*
  * allow turning changes, see http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-tuning-changes/
  */
    p->ITerm += Ki * Perror;

  p->output = output;
  p->PrevInput = input;
}

/* Read the encoder values and call the PID routine */
void updatePID() 
	{
  /* Read the encoders */
  leftPID.Encoder = CountL;
  rightPID.Encoder = CountR;
  
  /* If we're not moving there is nothing more to do */
  if (moving==0)
		{
    /*
    * Reset PIDs once, to prevent startup spikes,
    * see http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-initialization/
    * PrevInput is considered a good proxy to detect
    * whether reset has already happened
    */
    if (leftPID.PrevInput != 0 || rightPID.PrevInput != 0) resetPID();
    return;
  }
	
  /* Compute PID update for each motor */
  doPID(&rightPID);
  doPID(&leftPID);

  /* Set the motor speeds accordingly */
  setMotorSpeeds(leftPID.output, rightPID.output);
	
	
}
#endif

#ifdef PidVel
int16_t UpdatePIDLeft(float TargetSpeed, float CurrentSpeed)
{
	float e;//cur error e(t)
	static float Last_e;//last error e(t-1)
	
	double P;
	double D;
	double I;
	static double Last_I;
	
	static int16_t last_u;
	int16_t u;
	
	e=TargetSpeed-CurrentSpeed;	
//	if(abs(e)<0.001)
//	{
//		e=0;
//	}
	P=Kp*e;
	I=Last_I+Ki*e;
	D=Kd*(e-Last_e);
	
	u=(P+I+D);//+last_u);
	
	//last_u=u;
	Last_e=e;
	Last_I=I;
	
	if((u<10)&(u>-10))
	{
		u=0;
	}
	
	return(u);
}

int16_t UpdatePIDRight(float TargetSpeed, float CurrentSpeed)
{
	float e;//cur error e(t)
	static float Last_e;//last error e(t-1)
	
	double P;
	double D;
	double I;
	static double Last_I;
	
	static int16_t last_u;
	int16_t u;
	
	e=TargetSpeed-CurrentSpeed;	
	
//	if(abs(e)<0.001)
//	{
//		e=0;
//	}
	
	P=Kp*e;
	I=Last_I+Ki*e;
	D=Kd*(e-Last_e);
	
	u=(P+I+D);//+last_u);
	
	last_u=u;
	Last_e=e;
	Last_I=I;
	
//	if(abs(u)<200)
//	{
//		u=0;
//	}
	
	return(u);
}

#endif 