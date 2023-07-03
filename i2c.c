#include "i2c.h"

void I2C_Init(const unsigned long baudRate) {
    SSPCON1  = 0x28;    // WCOL SSPOV   SSPEN CKP   SSPM3 SSPM2 SSPM1 SSPM0
    SSPCON2 = 0x00;     // GCEN ACKSTAT ACKDT ACKEN RCEN  PEN   RSEN  SEN
    SSPSTAT = 0x00;     // SMP  CKE     D/A   P(1)  S(1)  R/W   UA    BF
    SSPADD = (char)((_XTAL_FREQ/(4*baudRate))-1);
    SCL_D = 1;
    SDA_D = 1;
}

void I2C_Wait() {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Start() {
    I2C_Wait();
    SEN = 1;
}

void I2C_RepeatedStart() {
    I2C_Wait();
    RSEN = 1;
}

void I2C_Stop() {
    I2C_Wait();
    PEN = 1;
}

void I2C_ACK(void) {
    ACKDT = 0;			// 0 -> ACK
    I2C_Wait();
    ACKEN = 1;			// Send ACK
}

void I2C_NACK(void) {
    ACKDT = 1;			// 1 -> NACK
    I2C_Wait();
    ACKEN = 1;			// Send NACK
}

unsigned char I2C_Write(unsigned char data) {
    I2C_Wait();
    SSPBUF = data;
    while(!SSPIF);  // Wait Until Completion
    SSPIF = 0;
    return ACKSTAT;
}

unsigned char I2C_Read(void) {
    // Receive & Return A Byte
    I2C_Wait();
    RCEN = 1;       // Enable & Start Reception
    while(!SSPIF);  // Wait Until Completion
    SSPIF = 0;      // Clear The Interrupt Flag Bit
    I2C_Wait();
    return SSPBUF;  // Return The Received Byte
}
