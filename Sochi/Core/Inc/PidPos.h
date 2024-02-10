#include "main.h"

typedef struct PID{
	float TargetPositionMM;
	float CurrentPositionMM;
	float LastPosition;
	
	float CurrentError;
	float LastError;
	
	float CurrentVelMMs;
	//output
	float TargetVelMMs;
}PID;

void CulcVelMotorMS(PID *P);