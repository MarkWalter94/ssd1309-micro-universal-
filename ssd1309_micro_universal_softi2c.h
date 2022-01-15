/* 
 * File:   ssd1309_micro_universal_softi2c
 * Author: Marco Ortali
 *
 * Created on 14 gen 2022, 21.36
 */

#ifndef SOFT_I2C_H
#define SOFT_I2C_H

#ifdef __cplusplus
extern "C"
{
#endif

    void I2C_WriteRegister(char deviceAddress, char registerAddress, char data);
    void I2C_Delay();
    void SCL_Low();
    void SCL_High();
    void SDA_Low();
    void SDA_High();
    void I2C_SendZero();
    void I2C_SendOne();
    void I2C_Start();
    void I2C_Stop();
    void I2C_WriteByte(char);
    void I2C_WriteAddress(char deviceAddress);

    void I2C_Delay()
    {
        //TODO Implement a simple delay function..
        //10/50 us ~

        // Microchip code:

        // uint16_t kmt = 0;
        // for (kmt = 0; kmt < 100; ++kmt)
        // {
        //     asm("NOP");
        // }
    }

    void I2C_Delay10()
    {
        uint16_t kmt = 0;
        for (kmt = 0; kmt < 10; ++kmt)
        {
            I2C_Delay();
        }
    }

    void SCL_Low()
    {
        //TODO: Set SCL pin as output and pull it down.
    }

    void SCL_High()
    {
        //TODO: Set SCL pin as input.
    }

    void SDA_Low()
    {
        //TODO: Set SDA pin as output and pull it down.
    }

    void SDA_High()
    {
        //TODO: Set SDA pin as input.
    }

    void I2C_SendZero()
    {
        SCL_Low();
        SDA_Low();
        I2C_Delay();
        SCL_High();
        I2C_Delay();
        SCL_Low();
    }

    void I2C_SendOne()
    {
        SCL_Low();
        SDA_High();
        I2C_Delay();
        SCL_High();
        I2C_Delay();
        SCL_Low();
    }

    void I2C_Start()
    {
        SDA_High();
        SCL_High();
        I2C_Delay();
        SDA_Low();
        I2C_Delay();
        SCL_Low();

        I2C_Delay10();
    }

    void I2C_Stop()
    {
        SCL_Low();
        I2C_Delay();
        SDA_Low();
        I2C_Delay();
        SCL_High();
        I2C_Delay();
        SDA_High();
        I2C_Delay();
    }

    void I2C_WriteByte(char byteToSend)
    {
        for (int b = 0; b < 8; b++)
        {
            if ((byteToSend & 0x80) == 0x80)
                I2C_SendOne();
            else
                I2C_SendZero();
            byteToSend = byteToSend << 1;
        }

        //Stop bit
        I2C_SendOne();
    }

    void I2C_WriteAddress(char devAddr)
    {
        //Shift by 1 because we use a 8 bit address.
        devAddr = devAddr << 1;
        devAddr = devAddr & 0xFE;
        I2C_WriteByte(devAddr);
    }

    void I2C_WriteRegister(char devAddr, char regAddr, char byteToWrite)
    {
        //Write to the device, giving it the memory address to access
        I2C_Start();
        I2C_WriteAddress(devAddr);
        I2C_WriteByte(regAddr);
        I2C_WriteByte(byteToWrite);
        I2C_Stop();
    }

#ifdef __cplusplus
}
#endif

#endif /* SOFT_I2C_H */
