#include "main.h"
//#include "Defines.h"




/* PID setpoint info For a Motor */
typedef struct 
	{
  int32_t TargetTicksPerFrame;    // target speed in ticks per frame
  int32_t Encoder;                  // encoder count
  int32_t PrevEnc;                  // last encoder count

  /*
  * Using previous input (PrevInput) instead of PrevError to avoid derivative kick,
  * see http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-derivative-kick/
  */
  int32_t PrevInput;                // last input
  //int PrevErr;                   // last error

  /*
  * Using integrated term (ITerm) instead of integrated error (Ierror),
  * to allow tuning changes,
  * see http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-tuning-changes/
  */
  //int Ierror;
  int32_t ITerm;                    //integrated term

  int32_t output;                    // last motor setting
}
SetPointInfo;

//SetPointInfo leftPID, rightPID;

void resetPID();
void doPID(SetPointInfo *p);
void updatePID();
