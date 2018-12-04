/*******************************************************************************
* File Name: Slave_mosi.h  
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

#if !defined(CY_PINS_Slave_mosi_H) /* Pins Slave_mosi_H */
#define CY_PINS_Slave_mosi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Slave_mosi_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Slave_mosi__PORT == 15 && ((Slave_mosi__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Slave_mosi_Write(uint8 value);
void    Slave_mosi_SetDriveMode(uint8 mode);
uint8   Slave_mosi_ReadDataReg(void);
uint8   Slave_mosi_Read(void);
void    Slave_mosi_SetInterruptMode(uint16 position, uint16 mode);
uint8   Slave_mosi_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Slave_mosi_SetDriveMode() function.
     *  @{
     */
        #define Slave_mosi_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Slave_mosi_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Slave_mosi_DM_RES_UP          PIN_DM_RES_UP
        #define Slave_mosi_DM_RES_DWN         PIN_DM_RES_DWN
        #define Slave_mosi_DM_OD_LO           PIN_DM_OD_LO
        #define Slave_mosi_DM_OD_HI           PIN_DM_OD_HI
        #define Slave_mosi_DM_STRONG          PIN_DM_STRONG
        #define Slave_mosi_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Slave_mosi_MASK               Slave_mosi__MASK
#define Slave_mosi_SHIFT              Slave_mosi__SHIFT
#define Slave_mosi_WIDTH              1u

/* Interrupt constants */
#if defined(Slave_mosi__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Slave_mosi_SetInterruptMode() function.
     *  @{
     */
        #define Slave_mosi_INTR_NONE      (uint16)(0x0000u)
        #define Slave_mosi_INTR_RISING    (uint16)(0x0001u)
        #define Slave_mosi_INTR_FALLING   (uint16)(0x0002u)
        #define Slave_mosi_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Slave_mosi_INTR_MASK      (0x01u) 
#endif /* (Slave_mosi__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Slave_mosi_PS                     (* (reg8 *) Slave_mosi__PS)
/* Data Register */
#define Slave_mosi_DR                     (* (reg8 *) Slave_mosi__DR)
/* Port Number */
#define Slave_mosi_PRT_NUM                (* (reg8 *) Slave_mosi__PRT) 
/* Connect to Analog Globals */                                                  
#define Slave_mosi_AG                     (* (reg8 *) Slave_mosi__AG)                       
/* Analog MUX bux enable */
#define Slave_mosi_AMUX                   (* (reg8 *) Slave_mosi__AMUX) 
/* Bidirectional Enable */                                                        
#define Slave_mosi_BIE                    (* (reg8 *) Slave_mosi__BIE)
/* Bit-mask for Aliased Register Access */
#define Slave_mosi_BIT_MASK               (* (reg8 *) Slave_mosi__BIT_MASK)
/* Bypass Enable */
#define Slave_mosi_BYP                    (* (reg8 *) Slave_mosi__BYP)
/* Port wide control signals */                                                   
#define Slave_mosi_CTL                    (* (reg8 *) Slave_mosi__CTL)
/* Drive Modes */
#define Slave_mosi_DM0                    (* (reg8 *) Slave_mosi__DM0) 
#define Slave_mosi_DM1                    (* (reg8 *) Slave_mosi__DM1)
#define Slave_mosi_DM2                    (* (reg8 *) Slave_mosi__DM2) 
/* Input Buffer Disable Override */
#define Slave_mosi_INP_DIS                (* (reg8 *) Slave_mosi__INP_DIS)
/* LCD Common or Segment Drive */
#define Slave_mosi_LCD_COM_SEG            (* (reg8 *) Slave_mosi__LCD_COM_SEG)
/* Enable Segment LCD */
#define Slave_mosi_LCD_EN                 (* (reg8 *) Slave_mosi__LCD_EN)
/* Slew Rate Control */
#define Slave_mosi_SLW                    (* (reg8 *) Slave_mosi__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Slave_mosi_PRTDSI__CAPS_SEL       (* (reg8 *) Slave_mosi__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Slave_mosi_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Slave_mosi__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Slave_mosi_PRTDSI__OE_SEL0        (* (reg8 *) Slave_mosi__PRTDSI__OE_SEL0) 
#define Slave_mosi_PRTDSI__OE_SEL1        (* (reg8 *) Slave_mosi__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Slave_mosi_PRTDSI__OUT_SEL0       (* (reg8 *) Slave_mosi__PRTDSI__OUT_SEL0) 
#define Slave_mosi_PRTDSI__OUT_SEL1       (* (reg8 *) Slave_mosi__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Slave_mosi_PRTDSI__SYNC_OUT       (* (reg8 *) Slave_mosi__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Slave_mosi__SIO_CFG)
    #define Slave_mosi_SIO_HYST_EN        (* (reg8 *) Slave_mosi__SIO_HYST_EN)
    #define Slave_mosi_SIO_REG_HIFREQ     (* (reg8 *) Slave_mosi__SIO_REG_HIFREQ)
    #define Slave_mosi_SIO_CFG            (* (reg8 *) Slave_mosi__SIO_CFG)
    #define Slave_mosi_SIO_DIFF           (* (reg8 *) Slave_mosi__SIO_DIFF)
#endif /* (Slave_mosi__SIO_CFG) */

/* Interrupt Registers */
#if defined(Slave_mosi__INTSTAT)
    #define Slave_mosi_INTSTAT            (* (reg8 *) Slave_mosi__INTSTAT)
    #define Slave_mosi_SNAP               (* (reg8 *) Slave_mosi__SNAP)
    
	#define Slave_mosi_0_INTTYPE_REG 		(* (reg8 *) Slave_mosi__0__INTTYPE)
#endif /* (Slave_mosi__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Slave_mosi_H */


/* [] END OF FILE */
