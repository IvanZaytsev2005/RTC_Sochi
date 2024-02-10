#include "PidPos.h"
#include "Defines.h"

#ifdef PIDPos
void CulcVelMotorMS(PID *P)
{
	P->CurrentError=P->TargetPositionMM-P->CurrentPositionMM;
	P->CurrentVelMMs=P->CurrentError/PidTimeMs;
	
	if(P->CurrentError<=NormDeltaMM)
	{
		P->TargetVelMMs=0;
	}
	else
	{
		P->TargetVelMMs=0;
	}
	
	
	P->LastError=P->CurrentError;
}

#endif