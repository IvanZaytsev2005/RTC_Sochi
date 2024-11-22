#include "main.h"
//#include "PidVel.h"

void r_motor_forv(uint16_t Velocity);
void r_motor_back(uint16_t Velocity);
void r_motor_stop();
void l_motor_forv(uint16_t Velocity);
void l_motor_back(uint16_t Velocity);
void l_motor_stop();
void StartState();
void Update();
void ServoWrite1(uint16_t Angle);
void ServoWrite2(uint16_t Angle);
void ServoWrite3(uint16_t Angle);
void ServoWrite4(uint16_t Angle);
void ServoWrite5(uint16_t Angle);
uint16_t SMA(uint16_t *data, uint16_t New, uint8_t *CountPos);
uint8_t OutUart (int16_t *Accel, uint8_t *Buf);
uint16_t OutPlot(float data1, float data2, uint8_t *Buf);
void SpeedCulcTick();
uint16_t OutEnc(int32_t data1, int32_t data2, uint8_t *Buf);
uint16_t OutDistance(float data1, float data2, uint8_t *Buf);
void TransmitOK();
void setMotorSpeeds(int16_t VelL, int16_t VelR);
uint16_t HelpOut(uint8_t *Buf);

void ColorOut(uint32_t Color);