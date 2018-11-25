/*******************************************************************************
* File Name: Trigger1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Trigger1_H) /* Pins Trigger1_H */
#define CY_PINS_Trigger1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Trigger1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Trigger1__PORT == 15 && ((Trigger1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Trigger1_Write(uint8 value);
void    Trigger1_SetDriveMode(uint8 mode);
uint8   Trigger1_ReadDataReg(void);
uint8   Trigger1_Read(void);
void    Trigger1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Trigger1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Trigger1_SetDriveMode() function.
     *  @{
     */
        #define Trigger1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Trigger1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Trigger1_DM_RES_UP          PIN_DM_RES_UP
        #define Trigger1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Trigger1_DM_OD_LO           PIN_DM_OD_LO
        #define Trigger1_DM_OD_HI           PIN_DM_OD_HI
        #define Trigger1_DM_STRONG          PIN_DM_STRONG
        #define Trigger1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Trigger1_MASK               Trigger1__MASK
#define Trigger1_SHIFT              Trigger1__SHIFT
#define Trigger1_WIDTH              1u

/* Interrupt constants */
#if defined(Trigger1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Trigger1_SetInterruptMode() function.
     *  @{
     */
        #define Trigger1_INTR_NONE      (uint16)(0x0000u)
        #define Trigger1_INTR_RISING    (uint16)(0x0001u)
        #define Trigger1_INTR_FALLING   (uint16)(0x0002u)
        #define Trigger1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Trigger1_INTR_MASK      (0x01u) 
#endif /* (Trigger1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Trigger1_PS                     (* (reg8 *) Trigger1__PS)
/* Data Register */
#define Trigger1_DR                     (* (reg8 *) Trigger1__DR)
/* Port Number */
#define Trigger1_PRT_NUM                (* (reg8 *) Trigger1__PRT) 
/* Connect to Analog Globals */                                                  
#define Trigger1_AG                     (* (reg8 *) Trigger1__AG)                       
/* Analog MUX bux enable */
#define Trigger1_AMUX                   (* (reg8 *) Trigger1__AMUX) 
/* Bidirectional Enable */                                                        
#define Trigger1_BIE                    (* (reg8 *) Trigger1__BIE)
/* Bit-mask for Aliased Register Access */
#define Trigger1_BIT_MASK               (* (reg8 *) Trigger1__BIT_MASK)
/* Bypass Enable */
#define Trigger1_BYP                    (* (reg8 *) Trigger1__BYP)
/* Port wide control signals */                                                   
#define Trigger1_CTL                    (* (reg8 *) Trigger1__CTL)
/* Drive Modes */
#define Trigger1_DM0                    (* (reg8 *) Trigger1__DM0) 
#define Trigger1_DM1                    (* (reg8 *) Trigger1__DM1)
#define Trigger1_DM2                    (* (reg8 *) Trigger1__DM2) 
/* Input Buffer Disable Override */
#define Trigger1_INP_DIS                (* (reg8 *) Trigger1__INP_DIS)
/* LCD Common or Segment Drive */
#define Trigger1_LCD_COM_SEG            (* (reg8 *) Trigger1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Trigger1_LCD_EN                 (* (reg8 *) Trigger1__LCD_EN)
/* Slew Rate Control */
#define Trigger1_SLW                    (* (reg8 *) Trigger1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Trigger1_PRTDSI__CAPS_SEL       (* (reg8 *) Trigger1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Trigger1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Trigger1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Trigger1_PRTDSI__OE_SEL0        (* (reg8 *) Trigger1__PRTDSI__OE_SEL0) 
#define Trigger1_PRTDSI__OE_SEL1        (* (reg8 *) Trigger1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Trigger1_PRTDSI__OUT_SEL0       (* (reg8 *) Trigger1__PRTDSI__OUT_SEL0) 
#define Trigger1_PRTDSI__OUT_SEL1       (* (reg8 *) Trigger1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Trigger1_PRTDSI__SYNC_OUT       (* (reg8 *) Trigger1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Trigger1__SIO_CFG)
    #define Trigger1_SIO_HYST_EN        (* (reg8 *) Trigger1__SIO_HYST_EN)
    #define Trigger1_SIO_REG_HIFREQ     (* (reg8 *) Trigger1__SIO_REG_HIFREQ)
    #define Trigger1_SIO_CFG            (* (reg8 *) Trigger1__SIO_CFG)
    #define Trigger1_SIO_DIFF           (* (reg8 *) Trigger1__SIO_DIFF)
#endif /* (Trigger1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Trigger1__INTSTAT)
    #define Trigger1_INTSTAT            (* (reg8 *) Trigger1__INTSTAT)
    #define Trigger1_SNAP               (* (reg8 *) Trigger1__SNAP)
    
	#define Trigger1_0_INTTYPE_REG 		(* (reg8 *) Trigger1__0__INTTYPE)
#endif /* (Trigger1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Trigger1_H */


/* [] END OF FILE */
