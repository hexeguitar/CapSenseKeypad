/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "CapSenseKeypad.h"
#include "mk_term.h"
#include <stdlib.h>

#define SYSTICK_TICKS 4000

extern volatile uint8_t capSenseKeypad_readFlag; //CapSense change flag

CY_ISR_PROTO(SYSTICK_ISR);      //Systick interrupt proto


volatile uint32_t SystickDelay;

// #############################################################################
// ############### Systick ISR used for delay ##################################
CY_ISR(SYSTICK_ISR)
{
    if (SystickDelay) SystickDelay--;   
}

//##############################################################################
int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    capSenseKeypad_readFlag = 0;
    SystickDelay = 0;
    
    /* Map systick ISR to the user defined ISR. SysTick_IRQn is already defined in core_cm0.h file */
	CyIntSetSysVector((SysTick_IRQn + 16), SYSTICK_ISR);
	
    /* Enable Systick timer with desired period/number of ticks */
	SysTick_Config(SYSTICK_TICKS);
    
    UART_Start();
    I2C_Start();
    Keypad_INT_ClearInterrupt();
        
    keypadInit();

    tr_cls(0);      //clear terminal screen
    tr_attr(MKTERM_BOLD,MKTERM_YELLOW,MKTERM_BLACK);
    tr_locate(1,0);
    UART_UartPutString("CapSense Keypad\r\n");
    UART_UartPutString("(c) 2016 by Piotr Zapart\r\n");
    tr_attr(MKTERM_RESET,MKTERM_YELLOW,MKTERM_BLACK);
    tr_locate(5,0);

    for(;;)
    {
      
        if(capSenseKeypad_readFlag)     //Cap sense key changed
        {
            capSenseKeypad_readFlag = 0;
            keypadHandle();
            
        }
     
        if (SystickDelay == 0)
        {
            LED_BLU_Write(1);
            LED_RED_Write(1);
            LED_GRN_Write(1);
        }
        
    }
}

/* [] END OF FILE */
