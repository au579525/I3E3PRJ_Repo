/*******************************************************************************
* File Name: Echo.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Echo_H) /* Pins Echo_H */
#define CY_PINS_Echo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Echo_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Echo__PORT == 15 && ((Echo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Echo_Write(uint8 value) ;
void    Echo_SetDriveMode(uint8 mode) ;
uint8   Echo_ReadDataReg(void) ;
uint8   Echo_Read(void) ;
uint8   Echo_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Echo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Echo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Echo_DM_RES_UP          PIN_DM_RES_UP
#define Echo_DM_RES_DWN         PIN_DM_RES_DWN
#define Echo_DM_OD_LO           PIN_DM_OD_LO
#define Echo_DM_OD_HI           PIN_DM_OD_HI
#define Echo_DM_STRONG          PIN_DM_STRONG
#define Echo_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Echo_MASK               Echo__MASK
#define Echo_SHIFT              Echo__SHIFT
#define Echo_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Echo_PS                     (* (reg8 *) Echo__PS)
/* Data Register */
#define Echo_DR                     (* (reg8 *) Echo__DR)
/* Port Number */
#define Echo_PRT_NUM                (* (reg8 *) Echo__PRT) 
/* Connect to Analog Globals */                                                  
#define Echo_AG                     (* (reg8 *) Echo__AG)                       
/* Analog MUX bux enable */
#define Echo_AMUX                   (* (reg8 *) Echo__AMUX) 
/* Bidirectional Enable */                                                        
#define Echo_BIE                    (* (reg8 *) Echo__BIE)
/* Bit-mask for Aliased Register Access */
#define Echo_BIT_MASK               (* (reg8 *) Echo__BIT_MASK)
/* Bypass Enable */
#define Echo_BYP                    (* (reg8 *) Echo__BYP)
/* Port wide control signals */                                                   
#define Echo_CTL                    (* (reg8 *) Echo__CTL)
/* Drive Modes */
#define Echo_DM0                    (* (reg8 *) Echo__DM0) 
#define Echo_DM1                    (* (reg8 *) Echo__DM1)
#define Echo_DM2                    (* (reg8 *) Echo__DM2) 
/* Input Buffer Disable Override */
#define Echo_INP_DIS                (* (reg8 *) Echo__INP_DIS)
/* LCD Common or Segment Drive */
#define Echo_LCD_COM_SEG            (* (reg8 *) Echo__LCD_COM_SEG)
/* Enable Segment LCD */
#define Echo_LCD_EN                 (* (reg8 *) Echo__LCD_EN)
/* Slew Rate Control */
#define Echo_SLW                    (* (reg8 *) Echo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Echo_PRTDSI__CAPS_SEL       (* (reg8 *) Echo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Echo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Echo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Echo_PRTDSI__OE_SEL0        (* (reg8 *) Echo__PRTDSI__OE_SEL0) 
#define Echo_PRTDSI__OE_SEL1        (* (reg8 *) Echo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Echo_PRTDSI__OUT_SEL0       (* (reg8 *) Echo__PRTDSI__OUT_SEL0) 
#define Echo_PRTDSI__OUT_SEL1       (* (reg8 *) Echo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Echo_PRTDSI__SYNC_OUT       (* (reg8 *) Echo__PRTDSI__SYNC_OUT) 


#if defined(Echo__INTSTAT)  /* Interrupt Registers */

    #define Echo_INTSTAT                (* (reg8 *) Echo__INTSTAT)
    #define Echo_SNAP                   (* (reg8 *) Echo__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Echo_H */


/* [] END OF FILE */
