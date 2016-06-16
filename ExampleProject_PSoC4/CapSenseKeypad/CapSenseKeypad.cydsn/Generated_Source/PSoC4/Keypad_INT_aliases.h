/*******************************************************************************
* File Name: Keypad_INT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Keypad_INT_ALIASES_H) /* Pins Keypad_INT_ALIASES_H */
#define CY_PINS_Keypad_INT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Keypad_INT_0			(Keypad_INT__0__PC)
#define Keypad_INT_0_PS		(Keypad_INT__0__PS)
#define Keypad_INT_0_PC		(Keypad_INT__0__PC)
#define Keypad_INT_0_DR		(Keypad_INT__0__DR)
#define Keypad_INT_0_SHIFT	(Keypad_INT__0__SHIFT)
#define Keypad_INT_0_INTR	((uint16)((uint16)0x0003u << (Keypad_INT__0__SHIFT*2u)))

#define Keypad_INT_INTR_ALL	 ((uint16)(Keypad_INT_0_INTR))


#endif /* End Pins Keypad_INT_ALIASES_H */


/* [] END OF FILE */
