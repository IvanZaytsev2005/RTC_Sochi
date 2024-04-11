#include "main.h"

#define MIN_PWM 80

#define MAX_PWM 255
//flag:
#define RecieveOk 0
#define TimeOk 1
#define StartCulcSpeed 2
#define StartPidUpdate 3
#define StartSettingMan 4
#define StartMovServo5 5
#define FinishMovServo5 6

#define SmaN 10



#define ZeroStateServo1 125
#define ZeroStateServo2 180
#define ZeroStateServo3 180
#define ZeroStateServo4 160
#define ZeroStateServo5 93

#define MaxDegreeServo1 0

#define MinMotorPWM 100

#define DistMM 0.235
#define DiametrMM 105
#define DiametrM 0.105

#define SpeedServo5Right 1390
#define SpeedServo5Left 1480
#define SpeedServo5Stop 0

#define Servo5TestAngleRaw 1000//ms

#define TickPerMetrLeft 3733
#define TickPerMetrRight 4064

#define SettingMan 1

#define PidVel 1
//#define PidPos 1

#ifdef PidVel
	#define PidTimeMs 50
#endif


#ifdef PidPos
	#define PidTimeMs 100
	#define NormDeltaMM 5 //error no moving
#endif