#ifndef I2C_H
#define	I2C_H

#include <xc.h>

#define _XTAL_FREQ  20000000

#define SDA_D       TRISB0
#define SCL_D       TRISB1

void I2C_Init(const unsigned long baudRate);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
unsigned char I2C_Write(unsigned char data);
unsigned char I2C_Read(void);

#endif //I2C_H
