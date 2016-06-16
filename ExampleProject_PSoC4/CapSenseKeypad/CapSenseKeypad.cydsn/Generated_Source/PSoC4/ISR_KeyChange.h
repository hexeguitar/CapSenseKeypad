/*******************************************************************************
* File Name: ISR_KeyChange.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ISR_KeyChange_H)
#define CY_ISR_ISR_KeyChange_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_KeyChange_Start(void);
void ISR_KeyChange_StartEx(cyisraddress address);
void ISR_KeyChange_Stop(void);

CY_ISR_PROTO(ISR_KeyChange_Interrupt);

void ISR_KeyChange_SetVector(cyisraddress address);
cyisraddress ISR_KeyChange_GetVector(void);

void ISR_KeyChange_SetPriority(uint8 priority);
uint8 ISR_KeyChange_GetPriority(void);

void ISR_KeyChange_Enable(void);
uint8 ISR_KeyChange_GetState(void);
void ISR_KeyChange_Disable(void);

void ISR_KeyChange_SetPending(void);
void ISR_KeyChange_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_KeyChange ISR. */
#define ISR_KeyChange_INTC_VECTOR            ((reg32 *) ISR_KeyChange__INTC_VECT)

/* Address of the ISR_KeyChange ISR priority. */
#define ISR_KeyChange_INTC_PRIOR             ((reg32 *) ISR_KeyChange__INTC_PRIOR_REG)

/* Priority of the ISR_KeyChange interrupt. */
#define ISR_KeyChange_INTC_PRIOR_NUMBER      ISR_KeyChange__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_KeyChange interrupt. */
#define ISR_KeyChange_INTC_SET_EN            ((reg32 *) ISR_KeyChange__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_KeyChange interrupt. */
#define ISR_KeyChange_INTC_CLR_EN            ((reg32 *) ISR_KeyChange__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_KeyChange interrupt state to pending. */
#define ISR_KeyChange_INTC_SET_PD            ((reg32 *) ISR_KeyChange__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_KeyChange interrupt. */
#define ISR_KeyChange_INTC_CLR_PD            ((reg32 *) ISR_KeyChange__INTC_CLR_PD_REG)



#endif /* CY_ISR_ISR_KeyChange_H */


/* [] END OF FILE */
