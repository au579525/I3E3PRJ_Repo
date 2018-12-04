/*******************************************************************************
* File Name: Master_ss.h  
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

#if !defined(CY_PINS_Master_ss_H) /* Pins Master_ss_H */
#define CY_PINS_Master_ss_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Master_ss_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Master_ss__PORT == 15 && ((Master_ss__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Master_ss_Write(uint8 value);
void    Master_ss_SetDriveMode(uint8 mode);
uint8   Master_ss_ReadDataReg(void);
uint8   Master_ss_Read(void);
void    Master_ss_SetInterruptMode(uint16 position, uint16 mode);
uint8   Master_ss_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Master_ss_SetDriveMode() function.
     *  @{
     */
        #define Master_ss_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Master_ss_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Master_ss_DM_RES_UP          PIN_DM_RES_UP
        #define Master_ss_DM_RES_DWN         PIN_DM_RES_DWN
        #define Master_ss_DM_OD_LO           PIN_DM_OD_LO
        #define Master_ss_DM_OD_HI           PIN_DM_OD_HI
        #define Master_ss_DM_STRONG          PIN_DM_STRONG
        #define Master_ss_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Master_ss_MASK               Master_ss__MASK
#define Master_ss_SHIFT              Master_ss__SHIFT
#define Master_ss_WIDTH              1u

/* Interrupt constants */
#if defined(Master_ss__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Master_ss_SetInterruptMode() function.
     *  @{
     */
        #define Master_ss_INTR_NONE      (uint16)(0x0000u)
        #define Master_ss_INTR_RISING    (uint16)(0x0001u)
        #define Master_ss_INTR_FALLING   (uint16)(0x0002u)
        #define Master_ss_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Master_ss_INTR_MASK      (0x01u) 
#endif /* (Master_ss__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Master_ss_PS                     (* (reg8 *) Master_ss__PS)
/* Data Register */
#define Master_ss_DR                     (* (reg8 *) Master_ss__DR)
/* Port Number */
#define Master_ss_PRT_NUM                (* (reg8 *) Master_ss__PRT) 
/* Connect to Analog Globals */                                                  
#define Master_ss_AG                     (* (reg8 *) Master_ss__AG)                       
/* Analog MUX bux enable */
#define Master_ss_AMUX                   (* (reg8 *) Master_ss__AMUX) 
/* Bidirectional Enable */                                                        
#define Master_ss_BIE                    (* (reg8 *) Master_ss__BIE)
/* Bit-mask for Aliased Register Access */
#define Master_ss_BIT_MASK               (* (reg8 *) Master_ss__BIT_MASK)
/* Bypass Enable */
#define Master_ss_BYP                    (* (reg8 *) Master_ss__BYP)
/* Port wide control signals */                                                   
#define Master_ss_CTL                    (* (reg8 *) Master_ss__CTL)
/* Drive Modes */
#define Master_ss_DM0                    (* (reg8 *) Master_ss__DM0) 
#define Master_ss_DM1                    (* (reg8 *) Master_ss__DM1)
#define Master_ss_DM2                    (* (reg8 *) Master_ss__DM2) 
/* Input Buffer Disable Override */
#define Master_ss_INP_DIS                (* (reg8 *) Master_ss__INP_DIS)
/* LCD Common or Segment Drive */
#define Master_ss_LCD_COM_SEG            (* (reg8 *) Master_ss__LCD_COM_SEG)
/* Enable Segment LCD */
#define Master_ss_LCD_EN                 (* (reg8 *) Master_ss__LCD_EN)
/* Slew Rate Control */
#define Master_ss_SLW                    (* (reg8 *) Master_ss__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Master_ss_PRTDSI__CAPS_SEL       (* (reg8 *) Master_ss__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Master_ss_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Master_ss__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Master_ss_PRTDSI__OE_SEL0        (* (reg8 *) Master_ss__PRTDSI__OE_SEL0) 
#define Master_ss_PRTDSI__OE_SEL1        (* (reg8 *) Master_ss__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Master_ss_PRTDSI__OUT_SEL0       (* (reg8 *) Master_ss__PRTDSI__OUT_SEL0) 
#define Master_ss_PRTDSI__OUT_SEL1       (* (reg8 *) Master_ss__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Master_ss_PRTDSI__SYNC_OUT       (* (reg8 *) Master_ss__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Master_ss__SIO_CFG)
    #define Master_ss_SIO_HYST_EN        (* (reg8 *) Master_ss__SIO_HYST_EN)
    #define Master_ss_SIO_REG_HIFREQ     (* (reg8 *) Master_ss__SIO_REG_HIFREQ)
    #define Master_ss_SIO_CFG            (* (reg8 *) Master_ss__SIO_CFG)
    #define Master_ss_SIO_DIFF           (* (reg8 *) Master_ss__SIO_DIFF)
#endif /* (Master_ss__SIO_CFG) */

/* Interrupt Registers */
#if defined(Master_ss__INTSTAT)
    #define Master_ss_INTSTAT            (* (reg8 *) Master_ss__INTSTAT)
    #define Master_ss_SNAP               (* (reg8 *) Master_ss__SNAP)
    
	#define Master_ss_0_INTTYPE_REG 		(* (reg8 *) Master_ss__0__INTTYPE)
#endif /* (Master_ss__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Master_ss_H */


/* [] END OF FILE */
