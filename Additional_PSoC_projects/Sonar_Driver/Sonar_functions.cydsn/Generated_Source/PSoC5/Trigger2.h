/*******************************************************************************
* File Name: Trigger2.h  
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

#if !defined(CY_PINS_Trigger2_H) /* Pins Trigger2_H */
#define CY_PINS_Trigger2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Trigger2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Trigger2__PORT == 15 && ((Trigger2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Trigger2_Write(uint8 value);
void    Trigger2_SetDriveMode(uint8 mode);
uint8   Trigger2_ReadDataReg(void);
uint8   Trigger2_Read(void);
void    Trigger2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Trigger2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Trigger2_SetDriveMode() function.
     *  @{
     */
        #define Trigger2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Trigger2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Trigger2_DM_RES_UP          PIN_DM_RES_UP
        #define Trigger2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Trigger2_DM_OD_LO           PIN_DM_OD_LO
        #define Trigger2_DM_OD_HI           PIN_DM_OD_HI
        #define Trigger2_DM_STRONG          PIN_DM_STRONG
        #define Trigger2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Trigger2_MASK               Trigger2__MASK
#define Trigger2_SHIFT              Trigger2__SHIFT
#define Trigger2_WIDTH              1u

/* Interrupt constants */
#if defined(Trigger2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Trigger2_SetInterruptMode() function.
     *  @{
     */
        #define Trigger2_INTR_NONE      (uint16)(0x0000u)
        #define Trigger2_INTR_RISING    (uint16)(0x0001u)
        #define Trigger2_INTR_FALLING   (uint16)(0x0002u)
        #define Trigger2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Trigger2_INTR_MASK      (0x01u) 
#endif /* (Trigger2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Trigger2_PS                     (* (reg8 *) Trigger2__PS)
/* Data Register */
#define Trigger2_DR                     (* (reg8 *) Trigger2__DR)
/* Port Number */
#define Trigger2_PRT_NUM                (* (reg8 *) Trigger2__PRT) 
/* Connect to Analog Globals */                                                  
#define Trigger2_AG                     (* (reg8 *) Trigger2__AG)                       
/* Analog MUX bux enable */
#define Trigger2_AMUX                   (* (reg8 *) Trigger2__AMUX) 
/* Bidirectional Enable */                                                        
#define Trigger2_BIE                    (* (reg8 *) Trigger2__BIE)
/* Bit-mask for Aliased Register Access */
#define Trigger2_BIT_MASK               (* (reg8 *) Trigger2__BIT_MASK)
/* Bypass Enable */
#define Trigger2_BYP                    (* (reg8 *) Trigger2__BYP)
/* Port wide control signals */                                                   
#define Trigger2_CTL                    (* (reg8 *) Trigger2__CTL)
/* Drive Modes */
#define Trigger2_DM0                    (* (reg8 *) Trigger2__DM0) 
#define Trigger2_DM1                    (* (reg8 *) Trigger2__DM1)
#define Trigger2_DM2                    (* (reg8 *) Trigger2__DM2) 
/* Input Buffer Disable Override */
#define Trigger2_INP_DIS                (* (reg8 *) Trigger2__INP_DIS)
/* LCD Common or Segment Drive */
#define Trigger2_LCD_COM_SEG            (* (reg8 *) Trigger2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Trigger2_LCD_EN                 (* (reg8 *) Trigger2__LCD_EN)
/* Slew Rate Control */
#define Trigger2_SLW                    (* (reg8 *) Trigger2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Trigger2_PRTDSI__CAPS_SEL       (* (reg8 *) Trigger2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Trigger2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Trigger2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Trigger2_PRTDSI__OE_SEL0        (* (reg8 *) Trigger2__PRTDSI__OE_SEL0) 
#define Trigger2_PRTDSI__OE_SEL1        (* (reg8 *) Trigger2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Trigger2_PRTDSI__OUT_SEL0       (* (reg8 *) Trigger2__PRTDSI__OUT_SEL0) 
#define Trigger2_PRTDSI__OUT_SEL1       (* (reg8 *) Trigger2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Trigger2_PRTDSI__SYNC_OUT       (* (reg8 *) Trigger2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Trigger2__SIO_CFG)
    #define Trigger2_SIO_HYST_EN        (* (reg8 *) Trigger2__SIO_HYST_EN)
    #define Trigger2_SIO_REG_HIFREQ     (* (reg8 *) Trigger2__SIO_REG_HIFREQ)
    #define Trigger2_SIO_CFG            (* (reg8 *) Trigger2__SIO_CFG)
    #define Trigger2_SIO_DIFF           (* (reg8 *) Trigger2__SIO_DIFF)
#endif /* (Trigger2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Trigger2__INTSTAT)
    #define Trigger2_INTSTAT            (* (reg8 *) Trigger2__INTSTAT)
    #define Trigger2_SNAP               (* (reg8 *) Trigger2__SNAP)
    
	#define Trigger2_0_INTTYPE_REG 		(* (reg8 *) Trigger2__0__INTTYPE)
#endif /* (Trigger2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Trigger2_H */


/* [] END OF FILE */
