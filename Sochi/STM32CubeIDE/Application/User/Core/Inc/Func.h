#include "main.h"

void r_motor_forv(uint16_t Velocity);
void r_motor_back(uint16_t Velocity);
void r_motor_stop();
void StartState();
void Update();
void ServoWrite1(uint16_t Angle);
void ServoWrite2(uint16_t Angle);
void ServoWrite3(uint16_t Angle);
void ServoWrite4(uint16_t Angle);
void ServoWrite5(uint16_t Angle);
int16_t SMA(uint16_t *data, uint16_t New, uint8_t *CountPos);