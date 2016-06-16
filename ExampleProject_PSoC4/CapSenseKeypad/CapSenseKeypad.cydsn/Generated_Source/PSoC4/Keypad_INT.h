/*******************************************************************************
* File Name: Keypad_INT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Keypad_INT_H) /* Pins Keypad_INT_H */
#define CY_PINS_Keypad_INT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Keypad_INT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Keypad_INT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Keypad_INT_Read(void);
void    Keypad_INT_Write(uint8 value);
uint8   Keypad_INT_ReadDataReg(void);
#if defined(Keypad_INT__PC) || (CY_PSOC4_4200L) 
    void    Keypad_INT_SetDriveMode(uint8 mode);
#endif
void    Keypad_INT_SetInterruptMode(uint16 position, uint16 mode);
uint8   Keypad_INT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Keypad_INT_Sleep(void); 
void Keypad_INT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Keypad_INT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Keypad_INT_DRIVE_MODE_BITS        (3)
    #define Keypad_INT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Keypad_INT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Keypad_INT_SetDriveMode() function.
         *  @{
         */
        #define Keypad_INT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Keypad_INT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Keypad_INT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Keypad_INT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Keypad_INT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Keypad_INT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Keypad_INT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Keypad_INT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Keypad_INT_MASK               Keypad_INT__MASK
#define Keypad_INT_SHIFT              Keypad_INT__SHIFT
#define Keypad_INT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Keypad_INT_SetInterruptMode() function.
     *  @{
     */
        #define Keypad_INT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Keypad_INT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Keypad_INT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Keypad_INT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Keypad_INT__SIO)
    #define Keypad_INT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Keypad_INT__PC) && (CY_PSOC4_4200L)
    #define Keypad_INT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Keypad_INT_USBIO_DISABLE              ((uint32)(~Keypad_INT_USBIO_ENABLE))
    #define Keypad_INT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Keypad_INT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Keypad_INT_USBIO_ENTER_SLEEP          ((uint32)((1u << Keypad_INT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Keypad_INT_USBIO_SUSPEND_DEL_SHIFT)))
    #define Keypad_INT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Keypad_INT_USBIO_SUSPEND_SHIFT)))
    #define Keypad_INT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Keypad_INT_USBIO_SUSPEND_DEL_SHIFT)))
    #define Keypad_INT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Keypad_INT__PC)
    /* Port Configuration */
    #define Keypad_INT_PC                 (* (reg32 *) Keypad_INT__PC)
#endif
/* Pin State */
#define Keypad_INT_PS                     (* (reg32 *) Keypad_INT__PS)
/* Data Register */
#define Keypad_INT_DR                     (* (reg32 *) Keypad_INT__DR)
/* Input Buffer Disable Override */
#define Keypad_INT_INP_DIS                (* (reg32 *) Keypad_INT__PC2)

/* Interrupt configuration Registers */
#define Keypad_INT_INTCFG                 (* (reg32 *) Keypad_INT__INTCFG)
#define Keypad_INT_INTSTAT                (* (reg32 *) Keypad_INT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Keypad_INT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Keypad_INT__SIO)
    #define Keypad_INT_SIO_REG            (* (reg32 *) Keypad_INT__SIO)
#endif /* (Keypad_INT__SIO_CFG) */

/* USBIO registers */
#if !defined(Keypad_INT__PC) && (CY_PSOC4_4200L)
    #define Keypad_INT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Keypad_INT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Keypad_INT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Keypad_INT_DRIVE_MODE_SHIFT       (0x00u)
#define Keypad_INT_DRIVE_MODE_MASK        (0x07u << Keypad_INT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Keypad_INT_H */


/* [] END OF FILE */
