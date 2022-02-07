#include <stdio.h>
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"

#define SDA		RC4
#define SCK		RC3
#define SDA_DIR	TRISC4
#define SCK_DIR	TRISC3

#define I2C_SPEED	100
//**************************************************************************************
// Definition pour le capteur de pression
//**************************************************************************************
/**
 * @brief Barometer 4 description command.
 * @details Specified command for description of Barometer 4 Click driver.
 */
#define BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_POWER           0x609C
#define BAROMETER4_CMD_OP_MODE_T_FIRST_NORMAL              0x6825
#define BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_NOISE           0x70DF
#define BAROMETER4_CMD_OP_MODE_T_FIRST_ULTRA_LOW_NOISE     0x7866
#define BAROMETER4_CMD_OP_MODE_P_FIRST_LOW_POWER           0x401A
#define BAROMETER4_CMD_OP_MODE_P_FIRST_NORMAL              0x48A3
#define BAROMETER4_CMD_OP_MODE_P_FIRST_LOW_NOISE           0x5059
#define BAROMETER4_CMD_OP_MODE_P_FIRST_ULTRA_LOW_NOISE     0x58E0
#define BAROMETER4_CMD_SOFT_RESET                          0x805D
#define BAROMETER4_CMD_DEVICE_ID                           0xEFC8
#define BAROMETER4_CMD_READ_OTP                            0xC7F7
/**
 * @brief Barometer 4 description setting.
 * @details Specified setting for description of Barometer 4 Click driver.
 */
#define BAROMETER4_OP_MODE_LOW_POWER                       0
#define BAROMETER4_OP_MODE_NORMAL                          1
#define BAROMETER4_OP_MODE_LOW_NOISE                       2
#define BAROMETER4_OP_MODE_ULTRA_LOW_NOISE                 3
/**
 * @brief Barometer 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 4 Click driver.
 */
#define BAROMETER4_SET_DEV_ADDR          0x63
#define altitude6_ADDR                   0x77
/**
 * @brief Barometer 4 crc constants.
 * @details Specified constants for crc 
 * of Barometer 4 Click driver.
 */
#define BAROMETER4_POLYNOM                0x31
#define BAROMETER4_INIT_VAL               0xFF

/**
 * @brief Barometer 4 transmit temperature or pressure first constants.
 * @details Specified constants for temperature or pressure first 
 * of Barometer 4 Click driver.
 */
#define BAROMETER4_DATA_T_FIRST           0
#define BAROMETER4_DATA_P_FIRST           1

/**
 * @brief Barometer 4 operation mode selection constants.
 * @details Specified constants for operation mode selection
 * of Barometer 4 Click driver.
 */
#define BAROMETER4_OP_MODE_DELAY_LP       0
#define BAROMETER4_OP_MODE_DELAY_N        1
#define BAROMETER4_OP_MODE_DELAY_LN       2
#define BAROMETER4_OP_MODE_DELAY_ULN      3

// Definitions
//#define _XTAL_FREQ  16000000        // this is used by the __delay_ms(xx) and __delay_us(xx) functions
#define device_control_code  0b1010 // All I2C devices have a control code assigned to them.
                                    // and the control code for a serial eeprom is b'1010' : 100111111



void InitI2C(void);
void I2C_Start(void);
void I2C_Restart(void);
void I2C_Stop(void);
void I2C_Send_ACK(void);
void I2C_Send_NACK(void);
void IC2C_WriteByte(unsigned char);
void Send_I2C_ACK(void);
unsigned char I2C_ReadByte(void);
