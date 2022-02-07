#include <xc.h>
#include "I2C.h"


void InitI2C(void){

	SDA_DIR = 1;
	SCK_DIR = 1;
	
	SSPADD = ((_XTAL_FREQ/4000)/I2C_SPEED)-1;
	SSPSTAT = 0x80;
	SSPCON = 0x28;
	
}

void I2C_Start(void){

	PIR1bits.SSP1IF=0;          // clear SSP interrupt bit
    SSPCON2bits.SEN=1;          // send start bit
    while(!PIR1bits.SSP1IF);    // Wait for the SSPIF bit to go back high b
	
}

void I2C_Restart(void){

	SSPCON2bits.RSEN = 1;
	while(!PIR1bits.SSP1IF);
	PIR1bits.SSP1IF = 0;
	
}

void I2C_Stop(void){

	while(!PIR1bits.SSP1IF);
	PIR1bits.SSP1IF = 0;
}

void IC2C_WriteByte(unsigned char Byte){

	SSPBUF = Byte;
	while(!PIR1bits.SSP1IF);
	PIR1bits.SSP1IF = 0;
	
	//return SSPCON2bits.ACKSTAT;
	
}

unsigned char I2C_ReadByte(void){

	SSPCON2bits.RCEN = 1;
	while(!PIR1bits.SSP1IF);
	PIR1bits.SSP1IF = 0;
	
	return SSPBUF;

}

//**************************************************************************************
// Send one byte to SEE
//**************************************************************************************
void Send_I2C_Data(unsigned int databyte)
{
    PIR1bits.SSP1IF=0;          // clear SSP interrupt bit
    SSPBUF = databyte;          // send databyte
    while(!PIR1bits.SSP1IF);    // Wait for interrupt flag to go high indicating transmission is complete
}


//**************************************************************************************
// Read one byte from SEE
//**************************************************************************************
unsigned int Read_I2C_Data(void)
{
    PIR1bits.SSP1IF=0;          // clear SSP interrupt bit
    SSPCON2bits.RCEN=1;         // set the receive enable bit to initiate a read of 8 bits from the serial eeprom
    while(!PIR1bits.SSP1IF);    // Wait for interrupt flag to go high indicating transmission is complete    
    return (SSPBUF);            // Data from eeprom is now in the SSPBUF so return that value
}

//**************************************************************************************
// Send control byte to SEE (this includes 4 bits of device code, block select bits and the R/W bit)
//**************************************************************************************
// Notes:
// 1) The device code for serial eeproms is defined as '1010' which we are using in this example
// 2) RW_bit can only be a one or zero
// 3) Block address is only used for SEE devices larger than 4K, however on
// some other devices these bits may become the hardware address bits that allow you
// to put multiple devices of the same type on the same bus.  Read the datasheet
// on your particular serial eeprom device to be sure.
//**************************************************************************************
void Send_I2C_ControlByte(unsigned int BlockAddress,unsigned int RW_bit)
{
    PIR1bits.SSP1IF=0;          // clear SSP interrupt bit

    // Assemble the control byte from device code, block address bits and R/W bit
    // so it looks like this: CCCCBBBR
    // where 'CCCC' is the device control code
    // 'BBB' is the block address
    // and 'R' is the Read/Write bit

    SSPBUF = ( (BlockAddress <<1)) + RW_bit;  // send the control byte (device_control_code << 4) |
    while(!PIR1bits.SSP1IF);    // Wait for interrupt flag to go high indicating transmission is complete
}

//**************************************************************************************
// Send start bit to SEE
//**************************************************************************************
void Send_I2C_StartBit(void)
{
    PIR1bits.SSP1IF=0;          // clear SSP interrupt bit
    SSPCON2bits.SEN=1;          // send start bit
    while(!PIR1bits.SSP1IF);    // Wait for the SSPIF bit to go back high before we load the data buffer
}

//**************************************************************************************
// Send stop bit to SEE
//**************************************************************************************
void Send_I2C_StopBit(void)
{
    PIR1bits.SSP1IF=0;          // clear SSP interrupt bit
    SSPCON2bits.PEN=1;          // send stop bit
    while(!PIR1bits.SSP1IF);    // Wait for interrupt flag to go high indicating transmission is complete
}


//**************************************************************************************
// Send ACK bit to SEE
//**************************************************************************************
void Send_I2C_ACK(void)
{
   PIR1bits.SSP1IF=0;          // clear SSP interrupt bit
   SSPCON2bits.ACKDT=0;        // clear the Acknowledge Data Bit - this means we are sending an Acknowledge or 'ACK'
   SSPCON2bits.ACKEN=1;        // set the ACK enable bit to initiate transmission of the ACK bit to the serial eeprom
   while(!PIR1bits.SSP1IF);    // Wait for interrupt flag to go high indicating transmission is complete
}

//**************************************************************************************
// Send NAK bit to SEE
//**************************************************************************************
void Send_I2C_NAK(void)
{
    PIR1bits.SSP1IF=0;           // clear SSP interrupt bit
    SSPCON2bits.ACKDT=1;        // set the Acknowledge Data Bit- this means we are sending a No-Ack or 'NAK'
    SSPCON2bits.ACKEN=1;        // set the ACK enable bit to initiate transmission of the ACK bit to the serial eeprom
    while(!PIR1bits.SSP1IF);    // Wait for interrupt flag to go high indicating transmission is complete
}