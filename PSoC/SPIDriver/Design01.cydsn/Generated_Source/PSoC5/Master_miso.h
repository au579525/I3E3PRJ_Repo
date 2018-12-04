/*******************************************************************************
* File Name: Master_miso.h  
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

#if !defined(CY_PINS_Master_miso_H) /* Pins Master_miso_H */
#define CY_PINS_Master_miso_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Master_miso_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Master_miso__PORT == 15 && ((Master_miso__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Master_miso_Write(uint8 value);
void    Master_miso_SetDriveMode(uint8 mode);
uint8   Master_miso_ReadDataReg(void);
uint8   Master_miso_Read(void);
void    Master_miso_SetInterruptMode(uint16 position, uint16 mode);
uint8   Master_miso_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Master_miso_SetDriveMode() function.
     *  @{
     */
        #define Master_miso_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Master_miso_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Master_miso_DM_RES_UP          PIN_DM_RES_UP
        #define Master_miso_DM_RES_DWN         PIN_DM_RES_DWN
        #define Master_miso_DM_OD_LO           PIN_DM_OD_LO
        #define Master_miso_DM_OD_HI           PIN_DM_OD_HI
        #define Master_miso_DM_STRONG          PIN_DM_STRONG
        #define Master_miso_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Master_miso_MASK               Master_miso__MASK
#define Master_miso_SHIFT              Master_miso__SHIFT
#define Master_miso_WIDTH              1u

/* Interrupt constants */
#if defined(Master_miso__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Master_miso_SetInterruptMode() function.
     *  @{
     */
        #define Master_miso_INTR_NONE      (uint16)(0x0000u)
        #define Master_miso_INTR_RISING    (uint16)(0x0001u)
        #define Master_miso_INTR_FALLING   (uint16)(0x0002u)
        #define Master_miso_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Master_miso_INTR_MASK      (0x01u) 
#endif /* (Master_miso__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Master_miso_PS                     (* (reg8 *) Master_miso__PS)
/* Data Register */
#define Master_miso_DR                     (* (reg8 *) Master_miso__DR)
/* Port Number */
#define Master_miso_PRT_NUM                (* (reg8 *) Master_miso__PRT) 
/* Connect to Analog Globals */                                                  
#define Master_miso_AG                     (* (reg8 *) Master_miso__AG)                       
/* Analog MUX bux enable */
#define Master_miso_AMUX                   (* (reg8 *) Master_miso__AMUX) 
/* Bidirectional Enable */                                                        
#define Master_miso_BIE                    (* (reg8 *) Master_miso__BIE)
/* Bit-mask for Aliased Register Access */
#define Master_miso_BIT_MASK               (* (reg8 *) Master_miso__BIT_MASK)
/* Bypass Enable */
#define Master_miso_BYP                    (* (reg8 *) Master_miso__BYP)
/* Port wide control signals */                                                   
#define Master_miso_CTL                    (* (reg8 *) Master_miso__CTL)
/* Drive Modes */
#define Master_miso_DM0                    (* (reg8 *) Master_miso__DM0) 
#define Master_miso_DM1                    (* (reg8 *) Master_miso__DM1)
#define Master_miso_DM2                    (* (reg8 *) Master_miso__DM2) 
/* Input Buffer Disable Override */
#define Master_miso_INP_DIS                (* (reg8 *) Master_miso__INP_DIS)
/* LCD Common or Segment Drive */
#define Master_miso_LCD_COM_SEG            (* (reg8 *) Master_miso__LCD_COM_SEG)
/* Enable Segment LCD */
#define Master_miso_LCD_EN                 (* (reg8 *) Master_miso__LCD_EN)
/* Slew Rate Control */
#define Master_miso_SLW                    (* (reg8 *) Master_miso__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Master_miso_PRTDSI__CAPS_SEL       (* (reg8 *) Master_miso__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Master_miso_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Master_miso__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Master_miso_PRTDSI__OE_SEL0        (* (reg8 *) Master_miso__PRTDSI__OE_SEL0) 
#define Master_miso_PRTDSI__OE_SEL1        (* (reg8 *) Master_miso__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Master_miso_PRTDSI__OUT_SEL0       (* (reg8 *) Master_miso__PRTDSI__OUT_SEL0) 
#define Master_miso_PRTDSI__OUT_SEL1       (* (reg8 *) Master_miso__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Master_miso_PRTDSI__SYNC_OUT       (* (reg8 *) Master_miso__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Master_miso__SIO_CFG)
    #define Master_miso_SIO_HYST_EN        (* (reg8 *) Master_miso__SIO_HYST_EN)
    #define Master_miso_SIO_REG_HIFREQ     (* (reg8 *) Master_miso__SIO_REG_HIFREQ)
    #define Master_miso_SIO_CFG            (* (reg8 *) Master_miso__SIO_CFG)
    #define Master_miso_SIO_DIFF           (* (reg8 *) Master_miso__SIO_DIFF)
#endif /* (Master_miso__SIO_CFG) */

/* Interrupt Registers */
#if defined(Master_miso__INTSTAT)
    #define Master_miso_INTSTAT            (* (reg8 *) Master_miso__INTSTAT)
    #define Master_miso_SNAP               (* (reg8 *) Master_miso__SNAP)
    
	#define Master_miso_0_INTTYPE_REG 		(* (reg8 *) Master_miso__0__INTTYPE)
#endif /* (Master_miso__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Master_miso_H */


/* [] END OF FILE */
