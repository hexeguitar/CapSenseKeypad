/* ========================================
 *
 * Cypress MBR3 Capsense controller driver
 * 
 * (c) 06.2016 Piotr Zapart
 * www.hexeguitar.com
 * 
 * ========================================
*/
#include <project.h>
#include <stdlib.h>
#include "MBR3.h"

 /* ========================================
 * Cap Sense Keypad *
 * ========================================
*/
#include <project.h>
#include "mk_term.h"
#include <stdlib.h>

#define CAPSENSE_KEYPAD_DEBUG ;

/* Configuration data created with Cypress EZ-Click */
const uint8_t MBR3_cfgData[128] = {
    0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x80u, 0x80u, 0x80u,
    0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
    0x80u, 0x80u, 0x80u, 0x80u, 0x03u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u,
    0x05u, 0x00u, 0x00u, 0x02u, 0x00u, 0x02u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u,
    0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u,
    0x00u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0x00u, 0x00u, 0x00u, 0x14u, 0x03u, 0x01u, 0x58u,
    0x00u, 0x37u, 0x0Fu, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xB6u, 0xBAu
};

// UART messages for debugging
#ifdef CAPSENSE_KEYPAD_DEBUG

    const char U_MSG_I2C[] = {"I2C "};
    const char U_MSG_I2C_ERR[] = {"Error"};
    const char U_MSG_I2C_WRITE[] = {"Write "};
    const char U_MSG_I2C_READ[] = {"Read "};
    const char U_MSG_I2C_OK[] = {"OK"};     
    const char U_MSG_NACK_TOUT[] = {"NACK timeout"};
#endif


uint32_t MBR3_init(void)
{   
    uint8_t *dataPtr = NULL;
    uint8_t dataByte;
    uint8_t result = 0;
    
    dataPtr = (uint8_t *)MBR3_cfgData;   
            
    //Send the 128bytes long config data

    result = MBR3_writeBuf(MBR3_SLAVE_ADDR,MBR3_REGMAP_ORIGIN,dataPtr,128);

    dataByte = MBR3_SAVE_CHECK_CRC;
    
    result = result | MBR3_writeBuf(MBR3_SLAVE_ADDR,MBR3_CTRL_CMD,&dataByte,1);
    
    CyDelay(300);  
   
    dataByte = MBR3_SW_RESET;
    result = result | MBR3_writeBuf(MBR3_SLAVE_ADDR,MBR3_CTRL_CMD,&dataByte,1);
      
    CyDelay(300);
    
    return result;
}

//##############################################################################
//      Write n bytes into MBR3 starting at regAddr address
//      based on the MBR3 datasheet, p.32
//      Master sends the Start condition and keeps resending (until timeout)
//      I2C_restart until the MBR3 chip wakes up and sends ACK
//      When the ACK is received, Master writes the start address pointer
//      and continues to write the data buffer. The operation ends with I2C_stop
//##############################################################################
uint32_t MBR3_writeBuf(uint8_t slaveAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length)
{
    uint8_t cnt = 0;
    uint8_t result;
    result = I2C_I2CMasterSendStart(slaveAddr, I2C_I2C_WRITE_XFER_MODE);        //send initial start condition
    while (result & I2C_I2C_MSTR_ERR_LB_NAK)                                    //keep sending repeat start
    {                                                                           //until MBR3 sends ACK
        result = I2C_I2CMasterSendRestart(slaveAddr, I2C_I2C_WRITE_XFER_MODE);
        cnt++;
        if (cnt == 50)
        {
            #ifdef CAPSENSE_KEYPAD_DEBUG
            UART_UartPutString("NACK timeout");
            UART_UartPutCRLF(0);
            #endif
            return I2C_I2C_MSTR_ERR_LB_NAK;
        }
        
    }
    
    if (result != I2C_I2C_MSTR_NO_ERROR)
    {
        #ifdef CAPSENSE_KEYPAD_DEBUG
        UART_UartPutString("writeBuf I2C Start Error= ");
           
        if (result & I2C_I2C_MSTR_BUS_BUSY)
        {
            UART_UartPutString("Bus busy ");           
        }
        else if (result & I2C_I2C_MSTR_NOT_READY)
        {
            UART_UartPutString("Master not ready ");
        }
        else if (result & I2C_I2C_MSTR_ERR_ARB_LOST)
        {
            UART_UartPutString("Arb. lost ");
        }
        else if (result & I2C_I2C_MSTR_ERR_BUS_ERR)
        {
            UART_UartPutString("Bus error ");
        }
        UART_UartPutCRLF(0);
        #endif
       
        return result;
    }
    
    
    // ### MBR3 sent ACK, write the register address ### 
    
    result = I2C_I2CMasterWriteByte(regAddr);  
    
    if (result != I2C_I2C_MSTR_NO_ERROR)
    {
        #ifdef CAPSENSE_KEYPAD_DEBUG
        UART_UartPutString("writeBuf Reg Address write Error= ");
           
        if (result & I2C_I2C_MSTR_BUS_BUSY)
        {
            UART_UartPutString("Bus busy ");           
        }
        else if (result & I2C_I2C_MSTR_NOT_READY)
        {
            UART_UartPutString("Master not ready ");
        }
        else if (result & I2C_I2C_MSTR_ERR_ARB_LOST)
        {
            UART_UartPutString("Arb. lost ");
        }
        else if (result & I2C_I2C_MSTR_ERR_BUS_ERR)
        {
            UART_UartPutString("Bus error ");
        }
        UART_UartPutCRLF(0);
        #endif
        
        I2C_I2CMasterSendStop();
        return result;
    }
        
    // ### Write data ###
    
    for (cnt = 0; cnt<length; cnt++)
    {
        result = I2C_I2CMasterWriteByte(buffer[cnt]);
        
        if (result != I2C_I2C_MSTR_NO_ERROR) 
        {
            #ifdef CAPSENSE_KEYPAD_DEBUG
            UART_UartPutString("Buffer write Error");
            UART_UartPutCRLF(0);
            #endif
        }
    }
    
    I2C_I2CMasterSendStop();
    
    return result;
}
//##############################################################################
//      Reads n bytes from MBR3 starting from addr address
//      based on the MBR3 datasheet, p.33
//      "waking up" the MBR3 chip works the same as in Write function
//##############################################################################
uint32_t MBR3_readBuf(uint8_t slaveAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length)
{  
    uint8_t result = 0;
    uint8_t cnt = 0;
    
    // first set the register address to be read from
    MBR3_writeBuf(slaveAddr,regAddr,&result,0);     //send regAddr only, result used as dummy byte
    
    // register address set, now read back the data
    result = I2C_I2CMasterSendStart(slaveAddr, I2C_I2C_READ_XFER_MODE);        //send initial start+read condition
    while (result & I2C_I2C_MSTR_ERR_LB_NAK)                                    //keep sending repeat start+read
    {                                                                           //until MBR3 sends ACK
        result = I2C_I2CMasterSendRestart(slaveAddr, I2C_I2C_READ_XFER_MODE);
        cnt++;
        if (cnt == 50)
        {
            #ifdef CAPSENSE_KEYPAD_DEBUG
            UART_UartPutString("readBuf NACK timeout");
            UART_UartPutCRLF(0);
            #endif
            return 0;
        }      
    }
    #ifdef CAPSENSE_KEYPAD_DEBUG
    if (result != I2C_I2C_MSTR_NO_ERROR)
    {
        UART_UartPutString("readBuf I2C Start Error= ");
           
        if (result & I2C_I2C_MSTR_BUS_BUSY)
        {
            UART_UartPutString("Bus busy ");           
        }
        else if (result & I2C_I2C_MSTR_NOT_READY)
        {
            UART_UartPutString("Master not ready ");
        }
        else if (result & I2C_I2C_MSTR_ERR_ARB_LOST)
        {
            UART_UartPutString("Arb. lost ");
        }
        else if (result & I2C_I2C_MSTR_ERR_BUS_ERR)
        {
            UART_UartPutString("Bus error ");
        }
        UART_UartPutCRLF(0);
    }
    #endif
    
    for(cnt = 0; cnt < length; cnt++)
	{
		if(cnt != length - 1)
			buffer[cnt] = (uint8_t)(I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA));
		else
			buffer[cnt] = (uint8_t)(I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA)); //last byte->send NACK
	}
    I2C_I2CMasterSendStop();
    
    return result; 
    
}


/* [] END OF FILE */

