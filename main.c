
#include "mcc_generated_files/mcc.h"
//#include "swuart.h"
#include <xc.h> // include standard header file
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"


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




//***********************      main 1     **************************************
void main() {
    
    // initialize the device
    SYSTEM_Initialize();
    SWUART_Initialize();
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    unsigned int tab[20];
    unsigned int i;
    volatile unsigned int data_P_first,incoming_data;
    volatile unsigned int block_address, word_address, word_address_r;
    unsigned char RxByte = 0;
    
    
    InitI2C();
    
    I2C_Start();
    IC2C_WriteByte(0xA0);
    RxByte = I2C_ReadByte();
    Send_I2C_ACK();
    I2C_Stop();

    while (1)
    {

        printf("Hello \t\n");
       printf("la valeur lue est :%c", RxByte);
       SWUART_Write (RxByte);
    }


}
/**
 End of File
*/